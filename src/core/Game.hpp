#pragma once

#include "../ecs/registry.hpp"
#include "../ecs/components.hpp"

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
		
		void update(float dt);
		void render();
		void testEntity();
};