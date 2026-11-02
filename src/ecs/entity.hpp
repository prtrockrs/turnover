#pragma once

class Entity {
	unsigned int e_id;
	unsigned static int id_count;

	public:
		Entity() {
			e_id = id_count++;
		}

		Entity(Entity& e) {
			e_id = e.e_id;
		}

		~Entity() {}

		operator unsigned int() { return e_id; }
		unsigned int id() { return e_id; }
};