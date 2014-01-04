#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Texture.h"
#include <GL/glew.h>
#include <string>
#include <unordered_map>

class TextureManager {

  public:
	
	~TextureManager();

	static TextureManager* instance();
	void clearCache();

	Texture* getTexture2D(std::string textureName);

  private:

	TextureManager();
	TextureManager(const TextureManager&);
	void operator=(const TextureManager&);

	static TextureManager m_sInstance;

	typedef std::unordered_map<std::string, Texture*> TextureMap;
	TextureMap m_xTextureCache;

	//void loadTexture(std::string textureName);
	//Texture* generateDummy();
};

#endif

