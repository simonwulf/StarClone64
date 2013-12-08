#include "Mesh.h"

Mesh::Mesh() {

	m_iVertexCount = 3;
	m_xVertices = new vertex[m_iVertexCount];
	
	//Test triangle
	m_xVertices[0].position = glm::vec3(-1.0f, -1.0f, 0.0f);
	m_xVertices[1].position = glm::vec3( 1.0f, -1.0f, 0.0f);
	m_xVertices[2].position = glm::vec3( 0.0f,  1.0f, 0.0f);

	m_xVertices[0].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_xVertices[1].color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_xVertices[2].color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	m_xVertices[0].texcoords = glm::vec2(0.0f);
	m_xVertices[1].texcoords = glm::vec2(0.0f);
	m_xVertices[2].texcoords = glm::vec2(0.0f);

	m_iIndexCount = 3;
	m_iIndices = new GLuint[m_iIndexCount];
	m_iIndices[0] = 0;
	m_iIndices[1] = 1;
	m_iIndices[2] = 2;

	//Set up OpenGL buffers
	void* ptr = &m_xGLBuffers;
	glGenBuffers(2, (GLuint*)&m_xGLBuffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_xGLBuffers.vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_xGLBuffers.index);

	glBufferData(GL_ARRAY_BUFFER, sizeof(m_xVertices[0])*m_iVertexCount, m_xVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_iIndices[0])*m_iIndexCount, m_iIndices, GL_STATIC_DRAW);
	//glBufferStorage(GL_ARRAY_BUFFER, sizeof(m_xVertices[0])*m_iVertexCount, m_xVertices, 0);
	//glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_iIndices[0])*m_iIndexCount, m_iIndices, 0);
}

Mesh::~Mesh() {

	delete [] m_xVertices;
	delete [] m_iIndices;

	glDeleteBuffers(2, (GLuint*)&m_xGLBuffers);
}

unsigned int Mesh::getVertexCount() const {

	return m_iVertexCount;
}

unsigned int Mesh::getTriCount() const {

	return m_iIndexCount / 3;
}

GLuint Mesh::getVertexBufferID() const {

	return m_xGLBuffers.vertex;
}

GLuint Mesh::getIndexBufferID() const {

	return m_xGLBuffers.index;
}