#include "RenderComponent.h"
#include "MeshManager.h"
#include "Renderer.h"

RenderComponent::RenderComponent() : Component(Component::Type::RENDER) {

	//Simple triangle mesh test
	m_xMesh = MeshManager::getMesh("test/mesh_test/pyramid.obj");//new Mesh();
}

RenderComponent::~RenderComponent() {

}

/*Mesh* RenderComponent::getMesh() const {

	return m_xMesh;
}*/

void RenderComponent::render() const {

	m_xMesh->quickTestDraw();
	//m_xMesh->draw(Renderer::m_xDefaultShaderProgram->glID());
}
