#include "stdafx.h"

#include "Mesh.h"

#include "LogManager.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <vector>
//#include <sstream>
#include <iostream>

Mesh::Mesh(unsigned int vertexCount, vertex* vertexArray, unsigned int indexCount, GLuint* indexArray, Material* material, GLuint usage) {
	
	m_iVertexCount = vertexCount;
	//m_xVertices = vertexArray;
	m_iIndexCount = indexCount;
	//m_iIndices = indexArray;

	m_xMaterial = material;

	glGenBuffers(2, (GLuint*)&m_xGLBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_xGLBuffers.vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_xGLBuffers.index);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * m_iVertexCount, vertexArray, usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_iIndexCount, indexArray, usage);
}

Mesh::~Mesh() {

	/* MeshManger handles cleanup */
	//delete [] m_xVertices;
	//delete [] m_iIndices;

	glDeleteBuffers(2, (GLuint*)&m_xGLBuffers);
}

unsigned int Mesh::getVertexCount() const {

	return m_iVertexCount;
}

unsigned int Mesh::getIndexCount() const {

	return m_iIndexCount;
}

unsigned int Mesh::getTriCount() const {

	return m_iIndexCount / 3;
}

const Material* Mesh::getMaterial() const {

	return m_xMaterial;
}

/*vertex* Mesh::getVertexArray() const {

	return m_xVertices;
}

GLuint* Mesh::getIndexArray() const {

	return m_iIndices;
}*/

GLuint Mesh::getVertexBufferID() const {

	return m_xGLBuffers.vertex;
}

GLuint Mesh::getIndexBufferID() const {

	return m_xGLBuffers.index;
}

/*void Mesh::setVertexArray( unsigned int vertCount, vertex* vertexArray ) {

	if(m_xVertices != nullptr)
		delete[] m_xVertices;
	m_iVertexCount = vertCount;
	m_xVertices = vertexArray;
}

void Mesh::setIndexArray( unsigned int indicesCount, GLuint* indexArray ) {

	if(m_iIndices != nullptr)
		delete[] m_iIndices;
	m_iIndexCount = indicesCount;
	m_iIndices = indexArray;
}*/

/*bool Mesh::isDummy() {

	return m_iVertexCount == 0;
}*/
