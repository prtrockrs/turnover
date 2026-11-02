#pragma once

#include "../ecs/registry.hpp"
#include "../systems/test_entity_system.hpp"

class Game {
	public:
		Game() = default;
		~Game();

		void init();
		void shutdown();
		void run();

	private:
		bool initialized = false;
		Registry registry;
		TestEntitySystem test_entity_system;
		
		void update(float dt);
		void render();
		void testEntity();
};