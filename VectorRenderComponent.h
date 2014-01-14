#ifndef VECTORRENDERCOMPONENT_H
#define VECTORRENDERCOMPONENT_H

#include "RenderComponent.h"

class VectorRenderComponent : public RenderComponent {

  public:

	VectorRenderComponent();

	void setVector(glm::vec3 vector);

	void render();

  private:

	struct vertex {
	
		glm::vec3 position;
	};

	static GLuint s_iVertexBufferID;

	vertex m_xVertices[2];
};

#endif