#ifndef HUDCONTROLLER_H
#define HUDCONTROLLER_H

#include "Component.h"

class GUITextureRenderComponent;

//View part of model-view-controller

class HUDController : public Component {

  public:

	HUDController();
	~HUDController();

	void init(GameObject* healthBar, GameObject* winText, GameObject* loseText);

  private:

	void update(const Event& e);

	GameObject* m_xHealthBar;
	GUITextureRenderComponent* m_xWinText;
	GUITextureRenderComponent* m_xLoseText;
};

#endif