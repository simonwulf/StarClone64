#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture {

  public:

	Texture(const std::string& filepath);
	~Texture();

	GLuint getTexID() const;

	//bool isDummy();

  private:
	
	GLuint m_iGLTextureID;
};

#endif