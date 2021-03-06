#include "GameObjects.h"
#include "Scene.h"

#include "ShaderManager.h"
#include "CollisionManager.h"
#include "ModelRenderComponent.h"
#include "GUITextureRenderComponent.h"
#include "PlayerController.h"
#include "LaserController.h"
#include "CameraController.h"
#include "PointLightComponent.h"
#include "PerspectiveCameraComponent.h"
#include "OrthographicCameraComponent.h"
#include "SkyboxCameraComponent.h"
#include "DirectionalLightComponent.h"
#include "SphereColliderComponent.h"
#include "EnemyHit.h"
#include "PlayerHit.h"
#include "SmallEnemyController.h"
#include "MainMenuController.h"

#undef near
#undef far

void Player::init() {

	GameObject* ship = getScene()->make("empty");
	ship->addComponent<ModelRenderComponent>()->init("spaceship/Spaceship.obj");
	addChild(ship);

	addComponent<PlayerController>()->init(ship);
	addComponent<PlayerHit>()->init(100);
	SphereColliderComponent* ssc = addComponent<SphereColliderComponent>();
	ssc->init(1.5f);
	ssc->setLayers(CollisionManager::PLAYER);
	ssc->setMask(CollisionManager::ENEMY);

	setTag("player");
}

void Laser::init(bool enemy) {

	setTag("laser");

	addComponent<ModelRenderComponent>()->init(enemy ? "laser/Laser_enemy.obj" : "laser/Laser.obj");
	addComponent<PointLightComponent>()->init(
		6.0f,
		enemy ? glm::vec3(1.0f, 0.5f, 0.5f) : glm::vec3(0.5f, 0.75f, 1.0f),
		1.0f
	);
	addComponent<LaserController>()->init(enemy);
}

void SmallEnemy::init() {

	setTag("small_enemy");

	addComponent<ModelRenderComponent>()->init("spaceship2/Spaceship2.obj");
	addComponent<EnemyHit>()->init(5);
	addComponent<SmallEnemyController>()->init();
	
	SphereColliderComponent* scc = addComponent<SphereColliderComponent>();
	scc->init(2.0f);
	scc->setLayers(CollisionManager::ENEMY);
	scc->setMask(CollisionManager::PLAYER);

	setScale(glm::vec3(0.6f, 0.6f, 0.6f));
}

void SimpleModel::init(const char* modelPath) {

	addComponent<ModelRenderComponent>()->init(modelPath);
}

void Skybox::init() {

	ModelRenderComponent* mrc = addComponent<ModelRenderComponent>();
	mrc->init("skybox/skybox.obj", ShaderManager::instance()->getProgram(SHADER_LIGHTING_UNLIT));
	for(unsigned int i = 0; i < mrc->getModel()->numMeshes(); ++i) {

		Mesh* meshes = mrc->getModel()->getMeshes();
		GLuint texId = meshes[i].getMaterial()->getTexture(meshes[i].getMaterial()->getIdsOfType(MATERIAL_DIFFUSE)[0])->getTexID();
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	setPosition(glm::vec3(0, -500, 0));
	setScale(glm::vec3(1000));
}

void PlayerCamera::init(GameObject* player, float fov, float near, float far, float ratio) {

	addComponent<PerspectiveCameraComponent>()->init(fov, near, far, ratio);
	addComponent<CameraController>()->init(player);

	setPosition(player->getPosition() + glm::vec3(0.0f, 0.0f, 5.0f));
}

void SkyCamera::init(float fov, float near, float far, float ratio) {

	addComponent<PerspectiveCameraComponent>()->init(fov, near, far, ratio);
	addComponent<SkyboxCameraComponent>()->init();
}

void SkyCamera::setReference(GameObject* refObj) {

	static_cast<SkyboxCameraComponent*>(getComponent(Component::CONTROLLER))->setReference(refObj);
}

void GUICamera::init(float width, float height) {

	addComponent<OrthographicCameraComponent>()->init(0.0f, width, height, 0.0f, -1.0f, 1.0f);
}

void GUITexture::init(const char* texturePath) {

	addComponent<GUITextureRenderComponent>()->init(texturePath);
}

void Sun::init(glm::vec3 direction, glm::vec3 color, float strength) {

	addComponent<DirectionalLightComponent>()->init(direction, color, strength);
}

void PointLight::init(glm::vec3 color, float radius, float strength) {

	addComponent<PointLightComponent>()->init(radius, color, strength);
}

void MainMenu::init() {

	GameObject* menuItemStart = getScene()->make("empty");
	GameObject* menuItemQuit = getScene()->make("empty");

	setTag("main_menu");
	menuItemStart->setName("item_start");
	menuItemQuit->setName("item_quit");

	menuItemStart->addComponent<ModelRenderComponent>()->init("text/start/start.obj");
	menuItemQuit->addComponent<ModelRenderComponent>()->init("text/quit/quit.obj");
	
	menuItemStart->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	menuItemQuit->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	menuItemStart->setRotation(glm::quat(glm::vec3(0.0f, 0.4f, 0.0f)));
	menuItemQuit->setRotation(glm::quat(glm::vec3(0.0f, 0.4f, 0.0f)));

	PointLight* light = getScene()->make<PointLight>("pointlight");
	light->init(glm::vec3(1.0f, 1.0f, 1.0f), 3.0f, 10.0f);
	light->setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

	addChild(menuItemStart);
	addChild(menuItemQuit);
	addChild(light);
	//addComponent<MainMenuController>()->init(mrc_start,mrc_quit,matSelected,matDeselected);
	addComponent<MainMenuController>()->init();
}