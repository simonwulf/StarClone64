#ifndef RAYCAST_H
#define RAYCAST_H

#include <glm/glm.hpp>

class Ray {

  public:

	Ray(glm::vec3 start, glm::vec3 direction, bool infinite = false, unsigned int mask = 0xffffffff) {
	
		this->start = start;
		this->direction = direction;
		this->infinite = infinite;
		this->mask = mask;
	}

	glm::vec3 start;
	glm::vec3 direction;
	bool infinite;
	unsigned int mask;
};

struct RaycastResult {
	
	GameObject* gameObject;
	glm::vec3 position;
	glm::vec3 normal;
	bool hit;
};

#endif