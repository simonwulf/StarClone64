#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Scene.h"
#include "SphereColliderComponent.h"

#include "Raycast.h"

class CollisionManager {

  public:

	enum Layer {
	  
		NONE = 0x00,
		WORLD = 0x02,
		PLAYER = 0x04,
		ENEMY = 0x08,

		ALL = 0xffffffff
	};

	static void checkCollisions(Scene* scene);
	static RaycastResult raycast(Ray ray, Scene* scene);

  private:

	static void sphereVsSphere(SphereColliderComponent* a, SphereColliderComponent* b);
};

#endif