#ifndef MODELRENDERCOMPONENT_H
#define MODELRENDERCOMPONENT_H

#include "RenderComponent.h"

#include "Model.h"

class ShaderProgram;

class ModelRenderComponent : public RenderComponent {

  public:

	void init(const char* filepath, ShaderProgram* defaultProgram = nullptr);
	void init(Model* model);

	void accept(Visitor* visitor);

	void render();

	Model* getModel() { return m_xModel; }

  private:

	Model* m_xModel;
};

#endif