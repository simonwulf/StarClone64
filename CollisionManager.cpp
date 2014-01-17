#include "CollisionManager.h"
#include "Profiler.h"

void CollisionManager::checkCollisions(Scene* scene) {

	PROFILE_START

	//TODO: Spatial partitioning
	Scene::ComponentList* list = scene->getComponents(Component::COLLIDER);

	for (unsigned int i = 0; (int)i < (int)(list->size() - 1); ++i) {
		for (unsigned int j = i+1; j < list->size(); ++j) {
		
			ColliderComponent* a = static_cast<ColliderComponent*>(list->at(i));
			ColliderComponent* b = static_cast<ColliderComponent*>(list->at(j));
			
			if (!(a->getLayers() & b->getMask()) &&
				!(b->getLayers() & a->getMask()))
				return;

			switch (a->getType()) {
			
				case ColliderComponent::SPHERE:
					switch (b->getType()) {
					
						case ColliderComponent::SPHERE:
							sphereVsSphere(static_cast<SphereColliderComponent*>(a), static_cast<SphereColliderComponent*>(b));
							break;
					}
					break;
			}
		}
	}

	PROFILE_END
}

RaycastResult CollisionManager::raycast(Ray ray, Scene* scene) {

	PROFILE_START

	RaycastResult best = {
		nullptr,
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		false
	};

	//TODO: Spatial partitioning
	Scene::ComponentList* list = scene->getComponents(Component::COLLIDER);

	float best_length = 0.0f;

	for (unsigned int i = 0; i < list->size(); ++i) {
	
		ColliderComponent* collider = static_cast<ColliderComponent*>(list->at(i));

		if (!(collider->getLayers() & ray.mask))
			continue;

		RaycastResult current = collider->raycast(ray);

		if (current.hit && (!best.hit || glm::length(current.position - ray.start) < best_length))
			best = current;
	}

	PROFILE_END

	return best;
}

void CollisionManager::sphereVsSphere(SphereColliderComponent* a, SphereColliderComponent* b) {

	GameObject* ago = a->getGameObject();
	GameObject* bgo = b->getGameObject();

	//if (ago == nullptr || bgo == nullptr)
	//	return;

	glm::vec3 diff(ago->getWorldPosition() - bgo->getWorldPosition());

	float length = glm::length(diff);

	if (length < a->getRadius() + b->getRadius()) { //Collision
	
		glm::vec3 push = glm::normalize(diff) * (a->getRadius() + b->getRadius() - length);
		glm::vec3 position = bgo->getWorldPosition() + glm::normalize(diff) * b->getRadius() - push;

		Event e(Event::COLLISION);
		e.collision.position.x = position.x;
		e.collision.position.y = position.y;
		e.collision.position.z = position.z;

		if (a->getMask() & b->getLayers()) {
			
			e.collision.other = bgo;
			e.collision.push.x = push.x;
			e.collision.push.y = push.y;
			e.collision.push.z = push.z;

			ago->dispatchEvent(e);
		}

		if (b->getMask() & a->getLayers()) {
			
			e.collision.other = a->getGameObject();
			e.collision.push.x = -push.x;
			e.collision.push.y = -push.y;
			e.collision.push.z = -push.z;

			bgo->dispatchEvent(e);
		}
	}
}