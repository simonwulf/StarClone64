#include "GameObject.h"
#include "RenderComponent.h"

GameObject::GameObject() {

	m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_vScale = glm::vec3(1.0f);
	m_qRotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);

	m_bUpdateMatrix = true;
	m_bUpdateInverseMatrix = true;

	m_xParent = nullptr;
}

GameObject::~GameObject() {
	
	for (unsigned int i = 0; i < m_xComponents.size(); ++i) {
	
		delete m_xComponents[i];
	}
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

const glm::mat4& GameObject::getInverseMatrix() {

	if (m_bUpdateInverseMatrix)
		m_mInverseMatrix = glm::inverse(getMatrix());

	return m_mInverseMatrix;
}

/*RenderComponent* GameObject::getRenderComponent() const {

	return m_xRenderComponent;
}*/

unsigned int GameObject::numChildren() const {

	return m_xChildren.size();
}

GameObject* GameObject::childAt(unsigned int index) const {

	return m_xChildren[index];
}

void GameObject::addChild(GameObject* child) {

	GameObject* current = this;

	while (current != nullptr) {
	
		if (current == child)
			throw std::invalid_argument("A GameObject cannot be added to itself");

		current = current->m_xParent;
	}

	if (child->m_xParent)
		m_xParent->removeChild(m_xParent);

	child->m_xParent = this;
	child->invalidateMatrix();

	m_xChildren.push_back(child);
}

void GameObject::removeChild(GameObject* child) {

	for (unsigned int i = 0; i < m_xChildren.size(); ++i) {

		if (m_xChildren[i] == child) {
		
			child->m_xParent = nullptr;
			m_xChildren.erase(m_xChildren.begin() + i);
			break;
		}
	}
}

void GameObject::addComponent(Component* component) {

	if (component->m_xGameObject != nullptr)
		throw std::invalid_argument("A component can not be moved between GameObjects");

	component->m_xGameObject = this;
	m_xComponents.push_back(component);
}

void GameObject::removeComponent(Component* component) {

	if (component->m_xGameObject != this)
		throw std::invalid_argument("A component can only be removed from it's own GameObject container");

	for (unsigned int i = 0; i < m_xComponents.size(); ++i) {
	
		if (m_xComponents[i] == component) {
		
			delete m_xComponents[i];
			m_xComponents.erase(m_xComponents.begin() + i);
			break;
		}
	}
}

Component* GameObject::getComponent(unsigned int type, unsigned int offset) {

	for (unsigned int i = offset; i < m_xComponents.size(); ++i) {
	
		if (m_xComponents[i]->getType() == type)
			return m_xComponents[i];
	}

	return nullptr;
}

unsigned int GameObject::getComponents(unsigned int type, Component* dest[]) {

	unsigned int num_found = 0;

	for (unsigned int i = 0; i < m_xComponents.size(); ++i) {
	
		if (m_xComponents[i]->getType() == type)
			dest[num_found++] = m_xComponents[i];
	}

	return num_found;
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
	invalidateMatrix();
}

void GameObject::setScale(const glm::vec3& scale) {

	m_vScale = scale;
	invalidateMatrix();
}

void GameObject::setRotation(const glm::quat& rotation) {

	m_qRotation = rotation;
	invalidateMatrix();
}

void GameObject::invalidateMatrix() {

	m_bUpdateMatrix = true;
	m_bUpdateInverseMatrix = true;

	for (unsigned int i = 0; i < m_xChildren.size(); ++i) {
	
		m_xChildren[i]->invalidateMatrix();
	}
}