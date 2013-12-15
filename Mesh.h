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

struct vertex {

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoords;
};

//Grouping buffer IDs as struct for readability
struct meshBufferIDs {
	GLuint vertex;
	GLuint index;
	const static short length = 2;
};

class Mesh {

  public:

	Mesh();
	~Mesh();

	unsigned int getVertexCount() const;
	unsigned int getIndexCount() const;
	unsigned int getTriCount() const;

	vertex* getVertexArray() const;
	GLuint* getIndexArray() const;

	void setVertexArray(unsigned int vertCount, vertex* vertexArray);
	void setIndexArray(unsigned int indicesCount, GLuint* indexArray);

	meshBufferIDs& getBufferIDs();
	GLuint getVertexBufferID();
	GLuint getIndexBufferID();

	bool isDummy();

  private:

	unsigned int m_iVertexCount;
	vertex* m_xVertices;

	unsigned int m_iIndexCount;
	GLuint* m_iIndices;

	meshBufferIDs m_xGLBuffers;
};

#endif