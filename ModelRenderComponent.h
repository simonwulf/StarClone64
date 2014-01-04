#ifndef MODELRENDERCOMPONENT_H
#define MODELRENDERCOMPONENT_H

#include "RenderComponent.h"
#include "Model.h"

class ModelRenderComponent : public RenderComponent {

  public:

	void init(const char* filepath);
	void init(const Model* model);

	void render();

  private:

	const Model* m_xModel;
};

#endif