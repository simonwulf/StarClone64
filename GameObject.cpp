#include "GameObject.h"
#include "RenderComponent.h"

GameObject::GameObject() {

	m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_vScale = glm::vec3(1.0f);
	m_qRotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);

	m_bUpdateMatrix = true;

	m_xParent = nullptr;

	//Test render component
	m_xRenderComponent = new RenderComponent();
}

GameObject::~GameObject() {
	
}

const glm::mat4& GameObject::getMatrix() {

	if (m_bUpdateMatrix) {
	
		m_mMatrix = m_xParent != nullptr ? m_xParent->getMatrix() : glm::mat4();

		m_mMatrix = glm::translate(m_mMatrix, m_vPosition);
		m_mMatrix *= glm::mat4_cast(m_qRotation);
		m_mMatrix = glm::scale(m_mMatrix, m_vScale);

		m_bUpdateMatrix = false;
	}

	return m_mMatrix;
}

RenderComponent* GameObject::getRenderComponent() const {

	return m_xRenderComponent;
}

unsigned int GameObject::numChildren() const {

	return m_xChildren.size();
}

GameObject* GameObject::childAt(unsigned int index) const {

	return m_xChildren[index];
}

const glm::vec3& GameObject::getPosition() const {

	return m_vPosition;
}

const glm::vec3& GameObject::getScale() const {

	return m_vScale;
}

const glm::quat& GameObject::getRotation() const {

	return m_qRotation;
}

void GameObject::setPosition(const glm::vec3& position) {

	m_vPosition = position;

	m_bUpdateMatrix = true;
}

void GameObject::setScale(const glm::vec3& scale) {

	m_vScale = scale;

	m_bUpdateMatrix = true;
}

void GameObject::setRotation(const glm::quat& rotation) {

	m_qRotation = rotation;

	m_bUpdateMatrix = true;
}