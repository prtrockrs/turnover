#pragma once

class Game {
	public:
		Game() = default;
		~Game();

		void init();
		void shutdown();
		void run();

	private:
		bool initialized = false;
		
		void update(float dt);
		void render();
};