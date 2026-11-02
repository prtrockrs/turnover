#include "Game.hpp"

#include <string>

#include "raylib.h"
#include "../ecs/entity.hpp"

const int DEFAULT_WINDOW_WIDTH = 1280;
const int DEFAULT_WINDOW_HEIGHT = 720;
const std::string GAME_WINDOW_NAME = "Turnover";

Game::~Game() {
    shutdown();
}

void Game::init() {
    InitWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, GAME_WINDOW_NAME.c_str());
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
}

void Game::render() {
}

void Game::shutdown() {
    if (!initialized) return;

    // Unload resources
    CloseWindow();

    initialized = false;
}

void Game::testEntity() {
	Entity e = registry.create_entity();
	registry.add<Position>(e, Position{ DEFAULT_WINDOW_WIDTH * 0.5, DEFAULT_WINDOW_HEIGHT * 0.5 });
	registry.add<Velocity>(e, Velocity{ 1.0, 1.0 });
}