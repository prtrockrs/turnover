#pragma once

#include "../ecs/registry.hpp"
#include "../core/game_config.hpp"

class TestEntitySystem {
	public:
		void update(Registry& registry) {
			for (unsigned int e : registry.view<Position, Velocity>()) {
				Position& pos = registry.get<Position>(e);
				Velocity& v = registry.get<Velocity>(e);

				if (pos.coords.x + v.dir.x > GameConfig::DEFAULT_WINDOW_WIDTH || pos.coords.x + v.dir.x < 0) {
					v.dir.x *= -1;
				}

				if (pos.coords.y + v.dir.y > GameConfig::DEFAULT_WINDOW_HEIGHT || pos.coords.y + v.dir.y < 0) {
					v.dir.y *= -1;
				}

				pos.coords.x += v.dir.x;
				pos.coords.y += v.dir.y;
			}
		}

		void render(Registry& registry) {
			for (unsigned e : registry.view<Position>()) {
				Position& pos = registry.get<Position>(e);
				DrawCircle(pos.coords.x, pos.coords.y, 7, RAYWHITE);
			}
		}
};