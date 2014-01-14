#include "GameObjects.h"
#include "Scene.h"

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
#include "SmallEnemyMovement.h"

#undef near
#undef far

void Player::init() {

	GameObject* ship = getScene()->make("empty");
	ship->addComponent<ModelRenderComponent>()->init("data/models/spaceship/Spaceship.obj");
	addChild(ship);

	addComponent<PlayerController>()->init(ship);
	addComponent<SphereColliderComponent>()->init(1.5f);

	setTag("player");
}

void Laser::init() {

	setTag("laser");

	addComponent<ModelRenderComponent>()->init("data/models/laser/Laser.obj");
	addComponent<PointLightComponent>()->init(6.0f, glm::vec3(0.5f, 0.75f, 1.0f), 1.0f);
	addComponent<LaserController>()->init();
}

void SmallEnemy::init() {

	setTag("enemy");

	addComponent<ModelRenderComponent>()->init("data/models/spaceship2/Spaceship2.obj");
	addComponent<EnemyHit>()->init(5);
	addComponent<SmallEnemyMovement>()->init();
	addComponent<SphereColliderComponent>()->init(2.0f);

	setScale(glm::vec3(0.6f, 0.6f, 0.6f));
}

void SimpleModel::init(const char* modelPath) {

	addComponent<ModelRenderComponent>()->init(modelPath);
}

void Skybox::init() {

	ModelRenderComponent* mrc = addComponent<ModelRenderComponent>();
	mrc->init("data/models/skybox/skybox.obj");
	for(unsigned int i = 0; i < mrc->getModel()->numMeshes(); ++i) {

		const Mesh* meshes = mrc->getModel()->getMeshes();
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

void SkyCamera::init(GameObject* refObj, float fov, float near, float far, float ratio) {

	addComponent<PerspectiveCameraComponent>()->init(fov, near, far, ratio);
	addComponent<SkyboxCameraComponent>()->init(refObj);
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