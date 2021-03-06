#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"
#include "Mesh.h"

class RenderComponent : public Component {

  public:

	RenderComponent();
	virtual ~RenderComponent();

	virtual void render() = 0;

	void setVisible(bool visible);
	bool getVisible() const;

private:

	bool m_bVisible;
};

#endif