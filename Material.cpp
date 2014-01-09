#include "Material.h"

#include "TextureManager.h"

Material::Material() {

	m_xTexLookup.resize(MATTYPE_LEN);
}

Material::~Material() {

}

void Material::addTexture(const char* filepath, MatType type) {

	m_xTextures.push_back(TextureManager::instance()->getTexture2D(filepath));
	m_xTexLookup[type].push_back(m_xTextures.size()-1);
}

unsigned int Material::numTexturesTotal() const {

	return m_xTextures.size();
}

const Texture* Material::getTexture(unsigned int index) const {

	return m_xTextures[index];
}

const std::vector<int>& Material::getIdsOfType( MatType type ) const{

	return m_xTexLookup[type];
}

unsigned int Material::numTextures( MatType type ) const {

	return m_xTexLookup[type].size();
}
