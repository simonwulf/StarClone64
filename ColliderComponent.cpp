#include "ColliderComponent.h"

#include "CollisionManager.h"

ColliderComponent::ColliderComponent(Type type) : Component(Component::COLLIDER) {

	m_iType = type;

	m_iCollisionLayers = CollisionManager::ALL;
	m_iCollisionMask = CollisionManager::ALL;
}

ColliderComponent::Type ColliderComponent::getType() {

	return m_iType;
}

void ColliderComponent::setLayers(unsigned int layers) {

	m_iCollisionLayers = layers;
}

unsigned int ColliderComponent::getLayers() const {

	return m_iCollisionLayers;
}

void ColliderComponent::setMask(unsigned int mask) {

	m_iCollisionMask = mask;
}

unsigned int ColliderComponent::getMask() const {

	return m_iCollisionMask;
}