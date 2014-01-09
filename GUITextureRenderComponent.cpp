#include "stdafx.h"

#include "GUITextureRenderComponent.h"

#include "Material.h"
#include "TextureManager.h"

GLuint GUITextureRenderComponent::s_iVertexBufferID = 0;
Material* GUITextureRenderComponent::s_xMaterial = nullptr;

GUITextureRenderComponent::GUITextureRenderComponent() {

	if (s_iVertexBufferID == 0) {
		
		glGenBuffers(1, &s_iVertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, s_iVertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 4, nullptr, GL_DYNAMIC_DRAW);
	}

	if (s_xMaterial == nullptr) {
	
		//TODO: make GUI material... or not
	}

	m_xTexture = nullptr;
}

void GUITextureRenderComponent::init(const char* texturePath) {

	m_xTexture = TextureManager::instance()->getTexture2D(texturePath);

	m_xVertices[1].position.y = (float)m_xTexture->getSize().y;
	m_xVertices[2].position.x = (float)m_xTexture->getSize().x;
	m_xVertices[2].position.y = (float)m_xTexture->getSize().y;
	m_xVertices[3].position.x = (float)m_xTexture->getSize().x;

	m_xVertices[0].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	m_xVertices[1].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	m_xVertices[2].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	m_xVertices[3].normal = glm::vec3(0.0f, 0.0f, 1.0f);

	m_xVertices[0].texture_coords.y = 1.0f;
	m_xVertices[2].texture_coords.x = 1.0f;
	m_xVertices[3].texture_coords.x = 1.0f;
	m_xVertices[3].texture_coords.y = 1.0f;
}

void GUITextureRenderComponent::render() {

	if (m_xTexture == nullptr)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, s_iVertexBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex)*4, &m_xVertices);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_xTexture->getTexID());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	//Vertex normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)sizeof(glm::vec3));
	//Vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)(sizeof(glm::vec3) * 2));

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}