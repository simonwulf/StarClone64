#include "ColliderComponent.h"
#include "SphereColliderComponent.h"

#include "Event.h"

ColliderComponent::ColliderComponent(Type type) : Component(Component::COLLIDER) {

	m_iType = type;
}

ColliderComponent::Type ColliderComponent::getType() {

	return m_iType;
}