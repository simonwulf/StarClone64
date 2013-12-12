#include "Texture.h"

Texture::Texture() {

	m_texID == 0;
}

Texture::~Texture() {

}

bool Texture::isDummy() {

	return m_texID == 0;
}

GLuint& Texture::getTexID() {

	return m_texID;
}