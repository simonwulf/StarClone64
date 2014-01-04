#ifndef RANDOMMOVER_H
#define RANDOMMOVER_H

#include <glm/core/type_vec3.hpp>
#include "ControllerComponent.h"
#include "Event.h"

class RandomMover : public ControllerComponent {

  public:

	RandomMover();
	~RandomMover();

	void update(const Event& e);

private:

	glm::vec3 m_vTarget;
	float m_fSpeed;

	void updateTarget();
};

#endif