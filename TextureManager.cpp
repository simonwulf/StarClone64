#include "TextureManager.h"
#include "LogManager.h"

TextureManager TextureManager::m_instance;

TextureManager::TextureManager() {

	m_textureTable = new std::unordered_map<std::string, Texture*>();
	Log::Writeln("TextureManager started.");
}

TextureManager::~TextureManager(void) {

	clearCache();
	delete m_textureTable;
}

Texture* TextureManager::getTexture2D( std::string textureName ) {

	Log::Write("Texture requested " + textureName + "\t");
	try {
		Texture* texture = getInstance().m_textureTable->at(textureName);

		#pragma region Logging
		Log::Write("returned from cache", Log::COLOR_LIGHT_AQUA);

		if(texture->isDummy())
			Log::Warn("\twarning: dummy texture!");
		else
			Log::Writeln("");
		#pragma endregion

		return texture;
	}
	catch (std::out_of_range) {
		getInstance().loadTexture(textureName);
		return getInstance().getTexture2D(textureName);
	}
}

void TextureManager::loadTexture( std::string textureName ) {

	Log::Write("loading texture " + textureName + "\t");
	FREE_IMAGE_FORMAT fileFormat;
	FIBITMAP* data = nullptr;

	fileFormat = FreeImage_GetFileType(textureName.c_str());
	if(fileFormat == FIF_UNKNOWN)
		fileFormat = FreeImage_GetFIFFromFilename(textureName.c_str());
	if(fileFormat == FIF_UNKNOWN)
	{
		Log::Err("error: couldn't read image format!");
		Texture* texture = generateDummy();
		m_textureTable->insert(std::make_pair<std::string, Texture*>(textureName, texture));
		return;
	}

	if(FreeImage_FIFSupportsReading(fileFormat))
		data = FreeImage_Load(fileFormat, textureName.c_str());

	if(data == nullptr)
	{
		Log::Err("error: couldn't load image!");
		Texture* texture = generateDummy();
		m_textureTable->insert(std::make_pair<std::string, Texture*>(textureName, texture));
		return;
	}

	FIBITMAP* temp = data;
	data = FreeImage_ConvertTo32Bits(data);
	FreeImage_Unload(temp);

	Texture* texture = new Texture();

	glGenTextures(1, &(texture->getTexID()));
	glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		FreeImage_GetWidth(data), 
		FreeImage_GetHeight(data),
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		FreeImage_GetBits(data)
	);

	FreeImage_Unload(data);

	m_textureTable->insert(std::make_pair<std::string, Texture*>(textureName, texture));

	Log::Success("success!");
}

void TextureManager::clearCache() {

	for(std::unordered_map<std::string, Texture*>::iterator it = getInstance().m_textureTable->begin();
		it != getInstance().m_textureTable->end(); ++it) {

		Texture* texture = it->second;

		glDeleteTextures(1, &(texture->getTexID()));
		delete texture;
	}

	getInstance().m_textureTable->clear();
	Log::Writeln("TextureManager cache cleared");
}

Texture* TextureManager::generateDummy() {

	return new Texture();
}