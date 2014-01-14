#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Scene.h"
#include "SphereColliderComponent.h"

#include "Raycast.h"

class CollisionManager {

public:

	static void checkCollisions(Scene* scene);
	static RaycastResult raycast(Ray ray, Scene* scene);

private:

	static void sphereVsSphere(SphereColliderComponent* a, SphereColliderComponent* b);
};

#endif