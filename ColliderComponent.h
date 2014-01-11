#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"

class SphereColliderComponent;

class ColliderComponent : Component {

  public:

	enum Type {
	
		SPHERE,
		PLANE,
		BOX,
	};

	ColliderComponent(Type type);

	virtual void checkCollision(ColliderComponent* other) = 0;

	Type getType();

  protected:

	static void sphereVsSphere(SphereColliderComponent* a, SphereColliderComponent* b);

  private:

	Type m_iType;
};

#endif