#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture {

  public:

	Texture();
	~Texture();

	GLuint& getTexID();

	bool isDummy();

	private:
		GLuint m_texID;
};

#endif