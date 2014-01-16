#include "MenuState.h"

#include "MenuGUIScene.h"
#include "SkyScene.h"
#include "CameraComponent.h"

MenuState::MenuState() {

	MenuGUIScene* menuScene = new MenuGUIScene();
	SkyScene* skyScene = new SkyScene();

	skyScene->setReference(menuScene->getCamera()->getGameObject());

	addScene(skyScene);
	addScene(menuScene);
}