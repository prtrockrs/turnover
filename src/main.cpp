#include "core/Game.hpp"

#include "raylib.h"
#include <stdio.h>

int main() {
	Game game = Game();

	game.init();
	game.run();
	game.shutdown();

	return 0;
}