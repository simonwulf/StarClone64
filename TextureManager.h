#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "MeshData.h"
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include "FreeImage.h"

class TextureManager {

	public:
		~TextureManager();

		static TextureManager& getInstance(){ return m_instance; }
		static void clearCache();

		static Texture* getTexture2D(std::string textureName, GLuint textureType);

	private:
		TextureManager();
		TextureManager(const TextureManager&);
		void operator=(const TextureManager&);

		static TextureManager m_instance;
		std::unordered_map<std::string, Texture*>* m_textureTable;

		void loadTexture(std::string textureName, GLuint textureType);
		Texture* generateDummy();
};

#endif

