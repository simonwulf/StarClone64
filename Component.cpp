#include "Component.h"

Component::Component(Component::Type type) {

	m_iType = type;

	m_xGameObject = nullptr;
}

Component::~Component() {

}

void Component::update(float delta, float elapsedTime) {

}

Component::Type Component::getType() {

	return m_iType;
}

GameObject* Component::getGameObject() {

	return m_xGameObject;
}