#include "GameObject.h"
#include "ComponentFactory.h"
#include "Component.h"

unsigned int GameObject::s_iAllocatedMemorySize = 0;

GameObject::GameObject() {

	m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_vScale = glm::vec3(1.0f);
	m_qRotation = glm::quat();

	m_bUpdateMatrix = true;
	m_bUpdateInverseMatrix = true;

	m_xParent = nullptr;
	m_xScene = nullptr;
}

GameObject::~GameObject() {
	
	for (unsigned int i = 0; i < m_xComponents.size(); ++i) {
	
		ComponentFactory::instance()->destroy(m_xComponents[i]);
	}
}

void* GameObject::operator new(size_t size) {

	void* ptr = ::operator new(size);
	s_iAllocatedMemorySize += _msize(ptr);

	return ptr;
}

void GameObject::operator delete(void* ptr) {

	s_iAllocatedMemorySize -= _msize(ptr);
	::operator delete(ptr);
}

unsigned int GameObject::getAllocatedMemorySize() {

	return s_iAllocatedMemorySize;
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

	if (m_bUpdateInverseMatrix) {
		
		m_mInverseMatrix = glm::inverse(getMatrix());

		m_bUpdateInverseMatrix = false;
	}

	return m_mInverseMatrix;
}

glm::vec3 GameObject::forward() {

	return glm::normalize(glm::vec3(getMatrix() * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
}

glm::vec3 GameObject::up() {

	return glm::normalize(glm::vec3(getMatrix() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
}

glm::vec3 GameObject::right() {

	return glm::normalize(glm::vec3(getMatrix() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
}

GameObject* GameObject::getParent() {

	return m_xParent;
}

Scene* GameObject::getScene() {

	return m_xScene;
}

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

	if (child->m_xParent != nullptr)
		m_xParent->removeChild(m_xParent);

	child->m_xParent = this;
	child->setScene(m_xScene);
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

	unsigned int count = 0;
	for (unsigned int i = 0; i < m_xComponents.size(); ++i) {
	
		if (m_xComponents[i]->getType() == type && offset == count++)
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

glm::vec3 GameObject::getPosition() const {

	return m_vPosition;
}

glm::vec3 GameObject::getWorldPosition() {

	return glm::vec3(glm::mat4(getMatrix()) * glm::vec4(0,0,0,1));
}


glm::vec3 GameObject::getScale() const {

	return m_vScale;
}

glm::quat GameObject::getRotation() const {

	return m_qRotation;
}

void GameObject::setPosition(glm::vec3 position) {

	m_vPosition = position;
	invalidateMatrix();
}

void GameObject::setScale(glm::vec3 scale) {

	m_vScale = scale;
	invalidateMatrix();
}

void GameObject::setRotation(glm::quat rotation) {

	m_qRotation = rotation;
	invalidateMatrix();
}

void GameObject::appendPosition(glm::vec3 position) {

	m_vPosition += position;
	invalidateMatrix();
}

void GameObject::appendScale(glm::vec3 scale) {

	m_vScale *= scale;
	invalidateMatrix();
}

void GameObject::appendRotation(glm::quat rotation) {

	m_qRotation = m_qRotation * rotation;
	invalidateMatrix();
}

void GameObject::lookAt(glm::vec3 target, glm::vec3 up) {

	glm::vec3 forward;
	glm::vec3 right;

	if (m_xParent != nullptr)
		forward = glm::vec3(m_xParent->getInverseMatrix() * glm::vec4(target, 1.0f)) - m_vPosition;
	else
		forward = target - m_vPosition;
	forward = glm::normalize(forward);

	if (m_xParent != nullptr)
		up = glm::normalize(glm::vec3(m_xParent->getInverseMatrix() * glm::vec4(up, 1.0f)));
	else
		up = glm::normalize(up);

	float dot = glm::dot(up, forward);

	if (dot == 1.0f || dot == -1.0f)
		right = glm::vec3(dot, 0.0f, 0.0f);
	else
		right = glm::normalize(glm::cross(forward, up));

	up = glm::cross(right, forward);

	setRotation(glm::quat(glm::mat3(right, up, -forward)));
}

void GameObject::setScene(Scene* scene) {

	m_xScene = scene;

	for (unsigned int i = 0; i < m_xChildren.size(); ++i) {
	
		m_xChildren[i]->setScene(scene);
	}
}

void GameObject::invalidateMatrix() {

	m_bUpdateMatrix = true;
	m_bUpdateInverseMatrix = true;

	for (unsigned int i = 0; i < m_xChildren.size(); ++i) {
	
		m_xChildren[i]->invalidateMatrix();
	}
}