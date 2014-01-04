#include "Texture.h"

#include "FreeImage.h"
#include "LogManager.h"

Texture::Texture(const std::string& filepath) {

	Log::Write("loading texture " + filepath + "\t");
	FREE_IMAGE_FORMAT fileFormat;
	FIBITMAP* data = nullptr;

	fileFormat = FreeImage_GetFileType(filepath.c_str());
	if(fileFormat == FIF_UNKNOWN)
		fileFormat = FreeImage_GetFIFFromFilename(filepath.c_str());
	if(fileFormat == FIF_UNKNOWN)
	{
		Log::Err("error: couldn't read image format!");
		m_iGLTextureID = 0;
		return;
	}

	if(FreeImage_FIFSupportsReading(fileFormat))
		data = FreeImage_Load(fileFormat, filepath.c_str());

	if(data == nullptr)
	{
		Log::Err("error: couldn't load image!");
		m_iGLTextureID = 0;
		return;
	}

	FIBITMAP* temp = data;
	data = FreeImage_ConvertTo32Bits(data);
	FreeImage_Unload(temp);

	glGenTextures(1, &m_iGLTextureID);
	glBindTexture(GL_TEXTURE_2D, m_iGLTextureID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		FreeImage_GetWidth(data), 
		FreeImage_GetHeight(data),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		FreeImage_GetBits(data)
	);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FreeImage_Unload(data);

	Log::Success("success!");
}

Texture::~Texture() {

	if (m_iGLTextureID != 0)
		glDeleteTextures(1, &m_iGLTextureID);
}

/*bool Texture::isDummy() {

	return m_texID == 0;
}*/

GLuint Texture::getTexID() const {

	return m_iGLTextureID;
}