#include "RenderComponent.h"

RenderComponent::RenderComponent() : Component(Component::Type::RENDER) {

	//Simple triangle mesh test
	m_xMesh = new Mesh();
}

RenderComponent::~RenderComponent() {

}

Mesh* RenderComponent::getMesh() const {

	return m_xMesh;
}