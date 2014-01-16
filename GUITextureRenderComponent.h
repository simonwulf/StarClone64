#ifndef GUITEXTURERENDERCOMPONENT_H
#define GUITEXTURERENDERCOMPONENT_H

#include "RenderComponent.h"

class Texture;
class Material;

class GUITextureRenderComponent : public RenderComponent {

  public:

	GUITextureRenderComponent();

	void init(const char* texturePath);

	void render();

	Texture* getTexture() const;

  private:

	struct vertex {
	
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture_coords;
	};

	static GLuint s_iVertexBufferID;
	static Material* s_xMaterial;

	Texture* m_xTexture;

	vertex m_xVertices[4];
};

#endif