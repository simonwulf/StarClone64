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

	void setLayers(unsigned int layers);
	unsigned int getLayers() const;
	void setMask(unsigned int mask);
	unsigned int getMask() const;

  private:

	Type m_iType;
	unsigned int m_iCollisionLayers;
	unsigned int m_iCollisionMask;
};

#endif