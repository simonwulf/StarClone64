#include "ColliderComponent.h"
#include "SphereColliderComponent.h"

#include "Event.h"

ColliderComponent::ColliderComponent(Type type) : Component(Component::COLLIDER) {

	m_iType = type;
}

ColliderComponent::Type ColliderComponent::getType() {

	return m_iType;
}

void ColliderComponent::sphereVsSphere(SphereColliderComponent* a, SphereColliderComponent* b) {

	GameObject* ago = a->getGameObject();
	GameObject* bgo = b->getGameObject();

	if (ago == nullptr || bgo == nullptr)
		return;

	glm::vec3 diff(ago->getWorldPosition() - bgo->getWorldPosition());

	float length = glm::length(diff);

	if (length > a->getRadius() + b->getRadius()) { //Collision
	
		glm::vec3 push = glm::normalize(diff) * (a->getRadius() + b->getRadius() - length) * 0.5f;
		glm::vec3 position = bgo->getWorldPosition() + glm::normalize(diff) * b->getRadius() - push;

		Event e(Event::COLLISION);
		e.collision.other = bgo;
		e.collision.position.x = position.x;
		e.collision.position.y = position.y;
		e.collision.position.z = position.z;
		e.collision.push.x = push.x;
		e.collision.push.y = push.y;
		e.collision.push.z = push.z;

		ago->dispatchEvent(e);

		e.collision.other = a->getGameObject();
		e.collision.push.x = -push.x;
		e.collision.push.y = -push.y;
		e.collision.push.z = -push.z;

		bgo->dispatchEvent(e);
	}
}