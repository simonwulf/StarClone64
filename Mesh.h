#ifndef MESH_H
#define MESH_H
/************************************************************************

Mesh is just a container for mesh data. It does not implement any 
functionality in itself except for getting and setting its values. 
All functionality is implemented by MeshManager which is also responsible 
for loading and returning meshes to object which utilize them.

************************************************************************/

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Material.h"

struct vertex {

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoords;
};

class Mesh {

  public:

	Mesh(unsigned int vertexCount, vertex* vertexArray, unsigned int indexCount, GLuint* indexArray, Material* material, GLuint usage = GL_STATIC_DRAW);
	~Mesh();

	unsigned int getVertexCount() const;
	unsigned int getIndexCount() const;
	unsigned int getTriCount() const;

	const Material* getMaterial() const;

	//vertex* getVertexArray() const;
	//GLuint* getIndexArray() const;

	//void setVertexArray(unsigned int vertCount, vertex* vertexArray);
	//void setIndexArray(unsigned int indicesCount, GLuint* indexArray);

	GLuint getVertexBufferID() const;
	GLuint getIndexBufferID() const;

	//bool isDummy();

  private:

	unsigned int m_iVertexCount;
	//vertex* m_xVertices;

	unsigned int m_iIndexCount;
	//GLuint* m_iIndices;

	Material* m_xMaterial;

	struct meshBufferIDs {
		
		GLuint vertex;
		GLuint index;
	
	} m_xGLBuffers;
};

#endif