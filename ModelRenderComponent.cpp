#include "ModelRenderComponent.h"
#include "ModelManager.h"
#include "Game.h"
#include "ShaderManager.h"

void ModelRenderComponent::init(const char* filepath, ShaderProgram* defaultProgram) {

	init(ModelManager::instance()->getModel(filepath));
	if(defaultProgram != nullptr && getModel()->getMeshes() != nullptr) {

		getModel()->getMeshes()[0].getMaterial()->setShaderProgram(defaultProgram);
	}
}

void ModelRenderComponent::init(Model* model) {

	m_xModel = model;
}

void ModelRenderComponent::render() {

	Mesh* meshes;
	ShaderProgram* shader = getModel()->getMeshes()[0].getMaterial()->getShaderProgram();
	glUseProgram(shader->glID());

	if (m_xModel == nullptr || (meshes = m_xModel->getMeshes()) == nullptr)
		return;

	/*	Setting of the uniforms is highly un-optimized. 
		Renderings should be sorted per program and use on glUseProgram per program.
		Operations marked with 'c' are constant and should only be set once per glUseProgram.

		Edit: changing rendering order to sort by shader would mess with drawing transparent materials.
	*/
	/* c */shader->uniformMatrix4fv("projection", 1, GL_FALSE, (GLfloat*) &getGameObject()->getScene()->getCamera()->getProjectionMatrix() );
	/* c */shader->uniformMatrix4fv("view", 1, GL_FALSE, (GLfloat*) &getGameObject()->getScene()->getCamera()->getViewMatrix() );
	/* c */shader->uniform3fv("ambient_light", 1, (GLfloat*) &getGameObject()->getScene()->getAmbientLight() );
	/* c */Game::instance()->getRenderer()->updateLights(LT_POINT, getGameObject()->getScene());
	/* c */Game::instance()->getRenderer()->updateLights(LT_DIRECTIONAL, getGameObject()->getScene());
	/* c */shader->uniform1ui("point_light_count", Game::instance()->getRenderer()->getLightCount(LT_POINT));
	/* c */shader->uniform1ui("dir_light_count", Game::instance()->getRenderer()->getLightCount(LT_DIRECTIONAL));
	shader->uniformMatrix4fv("model", 1, GL_FALSE, (GLfloat*) &getGameObject()->getMatrix());

	if((shader->shaderFlags() & SHADER_ALPHA_BLENDING_ADDITIVE)) {

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_MAX);
	} else {

		glDisable(GL_BLEND);
	}

	for (unsigned int i = 0; i < m_xModel->numMeshes(); ++i) {

		glBindBuffer(GL_ARRAY_BUFFER, meshes[i].getVertexBufferID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].getIndexBufferID());

		Material* material = meshes[i].getMaterial();
		if (material->numTextures(MATERIAL_DIFFUSE) > 0) {

			glActiveTexture(TEXSLOT_DIFFUSE);
			glBindTexture(GL_TEXTURE_2D, material->getTexture(material->getIdsOfType(MATERIAL_DIFFUSE)[0])->getTexID());
		}
		if (material->numTextures(MATERIAL_NORMALMAP) > 0) {

			glActiveTexture(TEXSLOT_NORMAL);
			glBindTexture(GL_TEXTURE_2D, material->getTexture(material->getIdsOfType(MATERIAL_NORMALMAP)[0])->getTexID());
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