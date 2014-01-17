#include "LoadingState.h"
#include "LoadingScene.h"
#include "SkyScene.h"
#include "CameraComponent.h"

LoadingState::LoadingState() {

	LoadingScene* loadingScene = new LoadingScene();
	SkyScene* skyScene = new SkyScene();

	skyScene->setReference(loadingScene->getCamera()->getGameObject());

	addScene(skyScene);
}