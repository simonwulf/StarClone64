#include "TextureManager.h"
#include "LogManager.h"

TextureManager TextureManager::m_sInstance;

TextureManager::TextureManager() {

	Log::Writeln("TextureManager started.");
}

TextureManager::~TextureManager(void) {

	clearCache();
}

TextureManager* TextureManager::instance() {

	return &m_sInstance;
}

Texture* TextureManager::getTexture2D(std::string filepath) {

	TextureMap::iterator itr = m_xTextureCache.find(filepath);
	Texture* ret;

	if (itr == m_xTextureCache.end()) {
	
		ret = new Texture(filepath);
		m_xTextureCache[filepath] = ret;
	} else {
	
		ret = itr->second;
	}

	return ret;
}

void TextureManager::clearCache() {

	for(TextureMap::iterator it = m_xTextureCache.begin(); it != m_xTextureCache.end(); ++it) {

		delete it->second;
	}

	m_xTextureCache.clear();
	Log::Writeln("TextureManager cache cleared");
}