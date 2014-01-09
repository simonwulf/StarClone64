#include "SkyScene.h"
#include "GOFactory.h"
#include "Game.h"

SkyScene::SkyScene() {

	setAmbientLight(glm::vec3(1));

	GameObject* skybox = GOFactory::instance()->createSkybox();
	add(skybox);
}

void SkyScene::init( GameObject* camRef ) {

	glm::ivec2 window_size = Game::instance()->getWindowSize();
	GameObject* camera = GOFactory::instance()->createSkyCamera(camRef, 60.0f, 0.1f, 1000.0f, (float)window_size.x/(float)window_size.y);
	add(camera);
	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));
}
