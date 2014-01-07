#include "Mesh.h"
#include <string>
#include <iostream>

SubMesh::SubMesh() {

	//Dummy constructor
}

SubMesh::SubMesh( std::vector<Vertex>* vertexData, std::vector<GLuint>* indexData, std::vector<Texture>* textureData /*= nullptr*/ ) {

	m_xVertices = *vertexData;
	m_iIndices = *indexData;
	if(textureData != nullptr)
		m_xTextures = *textureData;

	glGenBuffers(1, &m_iVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glBufferData(GL_ARRAY_BUFFER, m_xVertices.size()*sizeof(m_xVertices[0]), &m_xVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_iIND);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIND);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndices.size()*sizeof(m_iIndices[0]), &m_iIndices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

SubMesh::~SubMesh() {

	glDeleteBuffers(1, &m_iVBO);
	glDeleteBuffers(1, &m_iIND);
}

void SubMesh::draw( GLuint shader ) {

	if(m_xVertices.size() == 0)
		return;

	int attribVertex	= 1;
	int attribNormal	= 2;
	int attribTangent	= 3;
	int attribColor		= 4;
	int attribUV		= 5;

	std::string str = "texture";
	for(unsigned int i = 0; i < m_xTextures.size(); i++) {

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_xTextures[i].id);
		std::string texstr = str;
		texstr += i;
		glUniform1i(glGetUniformLocation(shader, texstr.c_str()), i);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIND);

	glEnableVertexAttribArray(attribVertex);
	glVertexAttribPointer(attribVertex, sizeof(glm::vec3), GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(attribNormal);
	glVertexAttribPointer(attribNormal, sizeof(glm::vec3), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)sizeof(glm::vec3));

	glEnableVertexAttribArray(attribTangent);
	glVertexAttribPointer(attribTangent, sizeof(glm::vec3), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(glm::vec3)*2));

	glEnableVertexAttribArray(attribColor);
	glVertexAttribPointer(attribColor, sizeof(glm::vec3), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(glm::vec3)*3));
	
	glEnableVertexAttribArray(attribUV);
	glVertexAttribPointer(attribUV, sizeof(glm::vec2), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(glm::vec3)*4));

	glDrawElements(GL_TRIANGLES, m_iIndices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(attribVertex);
	glDisableVertexAttribArray(attribNormal);
	glDisableVertexAttribArray(attribTangent);
	glDisableVertexAttribArray(attribColor);
	glDisableVertexAttribArray(attribUV);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw( GLuint shader ) {
	for(unsigned int i = 0; i < m_xMeshes->size(); i++) {

		(*m_xMeshes)[i]->draw(shader);
	}
}

void Mesh::quickTestDraw() {

	for(unsigned int i = 0; i < m_xMeshes->size(); i++) {

		glBindBuffer(GL_ARRAY_BUFFER, (*m_xMeshes)[i]->getVBO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*m_xMeshes)[i]->getIND());

		glDrawElements(GL_TRIANGLES, (*m_xMeshes)[i]->getICount(), GL_UNSIGNED_INT, 0);
	}
}

Mesh::Mesh() {

}

Mesh::~Mesh() {

	for(unsigned int i = 0; i < m_xMeshes->size(); i++) {
		delete (*m_xMeshes)[i];
	}

	delete m_xMeshes;
}
