#ifndef SPHERECOLLIDERCOMPONENT_H
#define SPHERECOLLIDERCOMPONENT_H

#include "ColliderComponent.h"

class SphereColliderComponent : public ColliderComponent {

  public:

	SphereColliderComponent();

	void init(float radius);

	void checkCollision(ColliderComponent* other);

	float getRadius();

  private:

	float m_fRadius;
};

#endif