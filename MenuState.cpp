#include "MenuState.h"

#include "MenuGUIScene.h"
#include "SkyScene.h"
#include "CameraComponent.h"
#include "SceneLoader.h"

MenuState::MenuState() {

	//MenuGUIScene* menuScene = new MenuGUIScene();
	SceneLoader loader;
	Scene* menuScene = loader.fromFile("data/scenes/menuscene.sc64");
	SkyScene* skyScene = new SkyScene();

	skyScene->setReference(menuScene->getCamera()->getGameObject());

	addScene(skyScene);
	addScene(menuScene);
}