#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

#include "Texture.h"
#include "Shader.h"

class Material {

  public:

	Material();
	~Material();

	void addTexture(const char* filepath);

	unsigned int numTextures() const;

	const Texture* getTexture(unsigned int index) const;

  private:

	std::vector<Texture*> m_xTextures;
	ShaderProgram* m_xShaderProgram; //Is this optimal? Or should we associate a material with only a fragment shader if we won't be using different vertex shaders?
};

#endif