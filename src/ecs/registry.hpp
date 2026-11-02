#pragma once

#include "component_container.hpp"
#include "entity.hpp"
#include "components.hpp"
#include <vector>
#include <memory>

// Registry class to manage entities
class Registry {
private:
	std::vector<unsigned int> entities;
	std::vector<std::unique_ptr<IComponentContainer>> component_containers;

	template<typename Component>
	ComponentContainer<Component>& get_container() {
		size_t type_id = component_type_id<Component>();
		return *static_cast<ComponentContainer<Component>*>(component_containers[type_id].get());
	}

	inline static size_t next_component_type_id = 0;

	template<typename T>
	static size_t component_type_id() {
		static size_t type_id = next_component_type_id++;
		return type_id;
	}

public:
	Registry() {}

	template<typename Component>
	void register_component() {
		size_t type_id = component_type_id<Component>();

		if (component_containers.size() <= type_id) component_containers.resize(type_id + 1);

		component_containers[type_id] = std::make_unique<ComponentContainer<Component>>();
	}

	Entity create_entity() {
		Entity e;
		entities.emplace_back(e);
		return e;
	}

	void remove_entity(unsigned int e) {
		for (auto& container : component_containers) {
			if (container) container->remove(e);
		}
		
		for (size_t i = 0; i < entities.size(); i++) {
			if (entities[i] == e) {
				entities[i] = entities.back();
				entities.pop_back();
				break;
			}
		}
	}

	void clear() {
		entities.clear();
		for (auto& container : component_containers) {
			if (container) container->clear();
		}
	}

	const std::vector<unsigned int>& get_entities() {
		return entities;
	}

	bool has_entity(Entity e) {
		for (auto& entity_id : entities) {
			if (entity_id == e.id()) {
				return true;
			}
		}
		return false;
	}

	// accessing components
	template<typename Component>
	bool has(unsigned int entity_id) {
		return get_container<Component>().has(entity_id);
	}

	template<typename Component>
	Component& get(unsigned int entity_id) {
		return get_container<Component>().get(entity_id);
	}

	template<typename Component>
	void add (unsigned int entity_id, const Component& component) {
		get_container<Component>().insert(entity_id, component);
	}

	template<typename Component>
	void remove(unsigned int entity_id) {
		get_container<Component>().remove(entity_id);
	}

	// get entities with various specified components
	template<typename First, typename... Rest>
	std::vector<unsigned int> view() {
		ComponentContainer<First>& primary = get_container<First>();

		std::vector<unsigned int> result;
		result.reserve(primary.entities().size());

		for (unsigned int entity_id : primary.entities()) {
			if ((... && has<Rest>(entity_id))) {
				result.emplace_back(entity_id);
			}
		}

		return result;
	}
};