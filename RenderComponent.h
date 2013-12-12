#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"
#include "Mesh.h"

class RenderComponent : public Component {

  public:

	RenderComponent();
	~RenderComponent();

	//Mesh* getMesh() const;

	void render() const;

  private:

	Mesh* m_xMesh;
	//Material* m_xMaterial;
	//ShaderProgram* m_xShaderProgram;
};

#endif