#include "GameObject.h"
#include "RenderComponent.h"

GameObject::GameObject() :
	m_vPosition(0.0f),
	m_vScale(1.0f),
	m_qRotation(0.0f, 0.0f, 0.0f, 1.0f)
{

	//Test render component
	m_xRenderComponent = new RenderComponent();
}

GameObject::~GameObject() {
	
}

RenderComponent* GameObject::getRenderComponent() const {

	return m_xRenderComponent;
}