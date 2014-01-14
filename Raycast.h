#ifndef RAYCAST_H
#define RAYCAST_H

#include <glm/glm.hpp>

struct Ray {

	glm::vec3 start;
	glm::vec3 direction;
	bool infinite;
};

struct RaycastResult {
	
	GameObject* gameObject;
	glm::vec3 position;
	glm::vec3 normal;
	bool hit;
};

#endif