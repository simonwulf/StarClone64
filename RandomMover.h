#ifndef RANDOMMOVER_H
#define RANDOMMOVER_H

#include "stdafx.h"
#include "ControllerComponent.h"

class RandomMover : public ControllerComponent {

  public:

	RandomMover();
	~RandomMover();

	void update(float delta, float elapsedTime);

private:

	glm::vec3 m_vTarget;
	float m_fSpeed;

	void updateTarget();
};

#endif