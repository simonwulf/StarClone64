#include "VectorRenderComponent.h"

GLuint VectorRenderComponent::s_iVertexBufferID = 0;

VectorRenderComponent::VectorRenderComponent() {

	if (s_iVertexBufferID == 0) {
		
		glGenBuffers(1, &s_iVertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, s_iVertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 2, nullptr, GL_DYNAMIC_DRAW);
	}

	m_xVertices[0].position = glm::vec3(0.0f);
}

void VectorRenderComponent::setVector(glm::vec3 vector) {

	m_xVertices[1].position = vector;
}

void VectorRenderComponent::render() {

	glBindBuffer(GL_ARRAY_BUFFER, s_iVertexBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex)*2, &m_xVertices);

	glEnableVertexAttribArray(0);

	//Vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);

	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(0);
}