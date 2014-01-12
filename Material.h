#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

#include "Texture.h"
#include "ShaderProgram.h"

enum MatType {

	MATERIAL_DIFFUSE,
	MATERIAL_NORMALMAP,

	MATTYPE_LEN
};

enum MaterialTextureSlots {

	TEXSLOT_DIFFUSE = GL_TEXTURE0,
	TEXSLOT_NORMAL = GL_TEXTURE1
};

class Material {

  public:

	Material();
	~Material();

	void addTexture(const char* filepath, MatType type);

	unsigned int numTextures(MatType type) const;
	unsigned int numTexturesTotal() const;

	const Texture* getTexture(unsigned int index) const;
	const std::vector<int>& getIdsOfType(MatType type) const;

	void setShaderProgram(ShaderProgram* prog);
	ShaderProgram* getShaderProgram();

  private:

	std::vector<Texture*> m_xTextures;
	std::vector<std::vector<int>> m_xTexLookup;
	ShaderProgram* m_xShaderProgram; //Is this optimal? Or should we associate a material with only a fragment shader if we won't be using different vertex shaders?
};

#endif