#include "core/Game.hpp"

#include "raylib.h"
#include <stdio.h>

int main() {
	InitWindow(500, 500, "test");
	printf("hi");

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}