#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"

#include "Raycast.h"

class ColliderComponent : public Component {

  public:

	enum Type {
	
		SPHERE,
		LINE,
		PLANE,
		BOX,
	};

	ColliderComponent(Type type);

	virtual RaycastResult raycast(Ray ray) = 0;

	Type getType();

  private:

	Type m_iType;
};

#endif