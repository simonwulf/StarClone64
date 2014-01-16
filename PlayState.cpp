#include "PlayState.h"

#include "PlayScene.h"
#include "SkyScene.h"
#include "HUDScene.h"
#include "CameraComponent.h"

PlayState::PlayState() {

	PlayScene* playScene = new PlayScene();
	SkyScene* skyScene = new SkyScene();
	HUDScene* hudScene = new HUDScene();

	skyScene->setReference(playScene->getCamera()->getGameObject());

	addScene(skyScene);
	addScene(playScene);
	addScene(hudScene);
}