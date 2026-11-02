#include "Game.hpp"

#include "raylib.h"
#include "../ecs/entity.hpp"
#include "game_config.hpp"

Game::~Game() {
    shutdown();
}

void Game::init() {
    InitWindow(GameConfig::DEFAULT_WINDOW_WIDTH, GameConfig::DEFAULT_WINDOW_HEIGHT, GameConfig::GAME_WINDOW_NAME.c_str());
    SetTargetFPS(60);

    // Initialize resources
    // Initialize systems
    // Create initial entities
	registry.register_component<Position>();
	registry.register_component<Velocity>();
	testEntity();

    initialized = true;
}

void Game::run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        update(deltaTime);

        BeginDrawing();

        ClearBackground(BLACK);

        render();

        EndDrawing();
    }
}

void Game::update(float deltaTime) {
	test_entity_system.update(registry);
}

void Game::render() {
	test_entity_system.render(registry);
}

void Game::shutdown() {
    if (!initialized) return;

    // Unload resources
    CloseWindow();

    initialized = false;
}

void Game::testEntity() {
	Entity e = registry.create_entity();
	registry.add<Position>(e, Position{
		static_cast<float>(GameConfig::DEFAULT_WINDOW_WIDTH * 0.5),
    	static_cast<float>(GameConfig::DEFAULT_WINDOW_HEIGHT * 0.5)
	});
	registry.add<Velocity>(e, Velocity{ 3.0, 3.0 });
}