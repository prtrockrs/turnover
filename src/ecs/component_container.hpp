#pragma once

#include <assert.h>
#include <vector>
#include <unordered_map>
#include "entity.hpp"

// base class for type-erased storage, less places to make changes
class IComponentContainer {
public:
    virtual ~IComponentContainer() = default;
    virtual void remove(unsigned int entity_id) = 0;
    virtual void clear() = 0;
    virtual bool has(unsigned int entity_id) const = 0;
};

// A container that stores components of type 'Component'
template <typename Component>
class ComponentContainer: public IComponentContainer {
private:
    std::vector<Component> components;
    std::vector<size_t> entity_to_index;
    std::vector<unsigned int> index_to_entity;

    static constexpr size_t INVALID = std::numeric_limits<size_t>::max();
public:
    ComponentContainer() {};

    // Inserts a component c associated to entity
    Component& insert(unsigned int entity_id, const Component& c) {
        if (entity_to_index.size() <= entity_id)
            entity_to_index.resize(entity_id + 1, INVALID);

        size_t new_index = components.size();

        components.emplace_back(c);
        index_to_entity.emplace_back(entity_id);
        entity_to_index[entity_id] = new_index;

        return components[new_index];
    }


    // Checks if entity e has a component of type 'Component'
    bool has(unsigned int entity_id) const override {
        return entity_id < entity_to_index.size() && entity_to_index[entity_id] != INVALID;
    }

    // Removes the component of type 'Component' from entity e
    void remove(unsigned int entity_id) override {
        if (!has(entity_id)) return;
        size_t index_to_remove = entity_to_index[entity_id];
        size_t last_index = components.size() - 1;
        if (index_to_remove != last_index) {
            components[index_to_remove] = components[last_index];

            unsigned int moving_entity = index_to_entity[last_index];
            index_to_entity[index_to_remove] = moving_entity;
            entity_to_index[moving_entity] = index_to_remove;
        }

        components.pop_back();
        index_to_entity.pop_back();
        entity_to_index[entity_id] = INVALID;
    }

    // Returns the component of type 'Component' associated with entity e
    Component& get(unsigned int entity_id) {
        return components[entity_to_index[entity_id]];
    };

    const std::vector<unsigned int>& entities() const {
        return index_to_entity;
    }

    void clear() override {
        components.clear();
        entity_to_index.clear();
        index_to_entity.clear();
    }

};