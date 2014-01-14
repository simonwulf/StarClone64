#ifndef SMALLENEMYMOVEMENT_H
#define SMALLENEMYMOVEMENT_H

#include "ControllerComponent.h"

class SmallEnemyMovement : public ControllerComponent {

public:

	~SmallEnemyMovement();

	void init();

private:

	glm::vec3 m_vTarget;
	float m_fMovementSpeed;

	void update(const Event& e);

	void changeTarget();
};

#endif