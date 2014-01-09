#include "ModelRenderComponent.h"
#include "ModelManager.h"
#include "Game.h"

void ModelRenderComponent::init(const char* filepath) {

	init(ModelManager::instance()->getModel(filepath));
}

void ModelRenderComponent::init(const Model* model) {

	m_xModel = model;
}

void ModelRenderComponent::render() {

	const Mesh* meshes;
	ShaderProgram* shader = Game::instance()->getRenderer()->getDefaultShader();

	if (m_xModel == nullptr || (meshes = m_xModel->getMeshes()) == nullptr)
		return;

	for (unsigned int i = 0; i < m_xModel->numMeshes(); ++i) {

		glBindBuffer(GL_ARRAY_BUFFER, meshes[i].getVertexBufferID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].getIndexBufferID());

		const Material* material = meshes[i].getMaterial();
		if (meshes[i].getMaterial()->numTextures(MATERIAL_DIFFUSE) > 0) {

			glActiveTexture(TEXSLOT_DIFFUSE);
			glBindTexture(GL_TEXTURE_2D, material->getTexture(material->getIdsOfType(MATERIAL_DIFFUSE)[0])->getTexID());
		}
		if (meshes[i].getMaterial()->numTextures(MATERIAL_NORMALMAP) > 0) {

			glActiveTexture(TEXSLOT_NORMAL);
			glBindTexture(GL_TEXTURE_2D, material->getTexture(material->getIdsOfType(MATERIAL_NORMALMAP)[0])->getTexID());
			shader->uniform1ui("use_normal", 1);
		}else {

			shader->uniform1ui("use_normal", 0);
		}

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		//Vertex positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		//Vertex normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)sizeof(glm::vec3));
		//Vertex texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)(sizeof(glm::vec3) * 2));
		//Vertex tangents
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)(sizeof(glm::vec3) * 2 + sizeof(glm::vec2)));

		glDrawElements(GL_TRIANGLES, meshes[i].getIndexCount(), GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}