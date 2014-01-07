#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Texture {

  public:

	Texture(const std::string& filepath);
	~Texture();

	GLuint getTexID() const;
	const glm::ivec2& getSize() const;

	//bool isDummy();

  private:
	
	GLuint m_iGLTextureID;
	glm::ivec2 m_vSize;
};

#endif