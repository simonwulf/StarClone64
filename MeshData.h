#ifndef MESHDATA_H
#define MESHDATA_H

#include <gl/glew.h>
#include <glm/glm.hpp>

struct Vertex {

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 color;
	glm::vec2 uv;
};

struct Texture {

	GLuint id;
	GLuint type;
};

static GLuint TEX_TYPE_DIFFUSE = 0;

#endif