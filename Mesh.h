#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

struct vertex {

	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texcoords;
};

class Mesh {

  public:

	Mesh();
	~Mesh();

	unsigned int getVertexCount() const;
	unsigned int getIndexCount() const;
	unsigned int getTriCount() const;

	GLuint getVertexBufferID() const;
	GLuint getIndexBufferID() const;

  private:

	unsigned int m_iVertexCount;
	vertex* m_xVertices;

	unsigned int m_iIndexCount;
	GLuint* m_iIndices;

	//Grouping buffer IDs as struct for readability
	struct {
		GLuint vertex;
		GLuint index;
	} m_xGLBuffers;
};

#endif