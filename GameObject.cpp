#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() :
	m_vPosition(0.0f),
	m_vScale(1.0f),
	m_xRotation(0.0f, 0.0f, 0.0f, 1.0f)
{

	memset(m_xComponents, 0, sizeof(Component*) * MAX_COMPONENTS);
}

GameObject::~GameObject() {
	
}