#include "SphereColliderComponent.h"

SphereColliderComponent::SphereColliderComponent() : ColliderComponent(ColliderComponent::SPHERE) {

	m_fRadius = 0.0f;
}

void SphereColliderComponent::init(float radius) {

	m_fRadius = radius;
}

void SphereColliderComponent::checkCollision(ColliderComponent* other) {

	switch (other->getType()) {
	
		case ColliderComponent::SPHERE:
			sphereVsSphere(this, static_cast<SphereColliderComponent*>(other));
			break;
	}
}

float SphereColliderComponent::getRadius() {

	return m_fRadius;
}