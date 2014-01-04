#include "ModelRenderComponent.h"
#include "ModelManager.h"

void ModelRenderComponent::init(const char* filepath) {

	init(ModelManager::instance()->getModel(filepath));
}

void ModelRenderComponent::init(const Model* model) {

	m_xModel = model;
}

void ModelRenderComponent::render() {

	const Mesh* meshes;
	const Material* materials;

	if (m_xModel == nullptr || (meshes = m_xModel->getMeshes()) == nullptr)
		return;

	//if ((materials = m_xModel->getMaterials()) != nullptr) {
		
		/*for (unsigned int i = 0; i < 1; ++i) { //Only using the first material for now
			for (unsigned int j = 0; j < materials[i].numTextures() && j < 32; ++j) {
			
				glActiveTexture(GL_TEXTURE0 + j);
				glBindTexture(GL_TEXTURE_2D, materials[i].getTexture(j)->getTexID());
			}
		}*/

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, materials[1].getTexture(0)->getTexID());
	//}

	for (unsigned int i = 0; i < m_xModel->numMeshes(); ++i) {

		glBindBuffer(GL_ARRAY_BUFFER, meshes[i].getVertexBufferID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].getIndexBufferID());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, meshes[i].getMaterial()->getTexture(0)->getTexID());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Vertex positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		//Vertex normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)sizeof(glm::vec3));
		//Vertex texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)(sizeof(glm::vec3) * 2));

		glDrawElements(GL_TRIANGLES, meshes[i].getIndexCount(), GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}