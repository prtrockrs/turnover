#include "Game.hpp"

#include "raylib.h"

Game::~Game() {
    shutdown();
}

void Game::init() {
    InitWindow(1280, 720, "My Game");
    SetTargetFPS(60);

    // Initialize resources
    // Initialize systems
    // Create initial entities

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