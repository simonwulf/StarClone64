#include "RenderComponent.h"
#include "MeshManager.h"

RenderComponent::RenderComponent() : Component(Component::Type::RENDER) {

	//Simple triangle mesh test
	m_xMesh = MeshManager::getMesh("test/mesh_test/teapot.obj");//new Mesh();
}

RenderComponent::~RenderComponent() {

}

/*Mesh* RenderComponent::getMesh() const {

	return m_xMesh;
}*/

void RenderComponent::render() const {

	glBindBuffer(GL_ARRAY_BUFFER, m_xMesh->getVertexBufferID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_xMesh->getIndexBufferID());

	glDrawElements(GL_TRIANGLES, m_xMesh->getIndexCount(), GL_UNSIGNED_INT, 0);
}
