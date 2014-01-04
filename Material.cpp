#include "Material.h"

#include "TextureManager.h"

Material::Material() {

}

Material::~Material() {

}

void Material::addTexture(const char* filepath) {

	m_xTextures.push_back(TextureManager::instance()->getTexture2D(filepath));
}

unsigned int Material::numTextures() const {

	return m_xTextures.size();
}

const Texture* Material::getTexture(unsigned int index) const {

	return m_xTextures[index];
}