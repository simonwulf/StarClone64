#include "GOFactory.h"

#include "LogManager.h"
#include "ComponentFactory.h"
#include "CameraComponent.h"
#include "ModelRenderComponent.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "TeapotSpin.h"
#include "RandomMover.h"
#include "PlayerController.h"
#include "LaserController.h"
#include "CameraController.h"
#include "PerspectiveCameraComponent.h"
#include "OrthographicCameraComponent.h"
#include "GUITextureRenderComponent.h"
#include "SkyboxCameraComponent.h"

GOFactory GOFactory::s_xInstance;

GOFactory::GOFactory() {

}

GOFactory* GOFactory::instance() {

	return &s_xInstance;
}

GameObject* GOFactory::createEmpty() {

	GameObject* empty = new GameObject();
	m_xProducts.push_back(empty);

	return empty;
}

GameObject* GOFactory::createTeapot() {

	GameObject* teapot = createEmpty();
	//teapot->setRotation(glm::angleAxis(-90.0f, 1.0f, 0.0f, 0.0f));
	//teapot->addComponent(ComponentFactory::instance()->create<RenderComponent>());
	teapot->addComponent<ModelRenderComponent>()->init("test/mesh_test/boss1/tris.md2");
	//teapot->addComponent<TeapotSpin>();

	//teapot->addComponent(ComponentFactory::instance()->create<RandomMover>());

	return teapot;
}

GameObject* GOFactory::createLaser() {

	GameObject* laser = createEmpty();

	laser->addComponent<ModelRenderComponent>()->init("data/models/laser/Laser.obj");
	laser->addComponent<LaserController>();
	laser->addComponent<PointLightComponent>()->init(3.0f, glm::vec3(0.5f, 0.75f, 1.0f), 1.0f);

	return laser;
}

GameObject* GOFactory::createPlayer() {

	GameObject* player = createEmpty();
	GameObject* ship = createEmpty();
	player->addChild(ship);

	ship->addComponent<ModelRenderComponent>()->init("data/models/spaceship2/Spaceship2.obj");
	player->addComponent<PlayerController>()->init(ship);

	return player;
}

GameObject* GOFactory::createSkybox() {

	GameObject* skybox = createEmpty();
	ModelRenderComponent* mrc = skybox->addComponent<ModelRenderComponent>();
	mrc->init("data/models/skybox/skybox.obj");
	for(unsigned int i = 0; i < mrc->getModel()->numMeshes(); ++i) {

		const Mesh* meshes = mrc->getModel()->getMeshes();
		GLuint texId = meshes[i].getMaterial()->getTexture(meshes[i].getMaterial()->getIdsOfType(MATERIAL_DIFFUSE)[0])->getTexID();
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	skybox->setPosition(glm::vec3(0, -500, 0));
	skybox->setScale(glm::vec3(1000));
	return skybox;
}


GameObject* GOFactory::createPlayerCamera(GameObject* player, float fov, float near, float far, float ratio) {

	GameObject* camera = createEmpty();

	camera->addComponent<PerspectiveCameraComponent>()->init(fov, near, far, ratio);
	camera->addComponent<CameraController>()->init(player);

	camera->setPosition(player->getPosition() + glm::vec3(0.0f, 0.0f, 5.0f));

	return camera;
}

GameObject* GOFactory::createGUICamera(float width, float height) {

	GameObject* camera = createEmpty();

	camera->addComponent<OrthographicCameraComponent>()->init(0.0f, width, height, 0.0f, -1.0f, 1.0f);

	return camera;
}

GameObject* GOFactory::createSkyCamera( GameObject* refObj, float fov, float near, float far, float ratio ) {

	GameObject* camera = createEmpty();
	camera->addComponent<PerspectiveCameraComponent>()->init(fov, near, far, ratio);
	camera->addComponent<SkyboxCameraComponent>()->init(refObj);

	return camera;
}

GameObject* GOFactory::createGroundPlane() {

	GameObject* plane = createEmpty();

	plane->addComponent<ModelRenderComponent>()->init("test/mesh_test/terrain_test.obj");

	return plane;
}

GameObject* GOFactory::createSun(glm::vec3 direction, glm::vec3 color, float strength) {

	GameObject* sun = createEmpty();
	
	DirectionalLightComponent* lightComponent = sun->addComponent<DirectionalLightComponent>();

	lightComponent->setDirection(direction);
	lightComponent->setColor(color);
	lightComponent->setStrength(strength);

	return sun;
}

GameObject* GOFactory::createPointLight(glm::vec3 color, float radius, float strength) {

	GameObject* light = createEmpty();
	
	light->addComponent<PointLightComponent>()->init(radius, color, strength);

	return light;
}

GameObject* GOFactory::createGUITest() {

	GameObject* guiTest = createEmpty();
	
	//guiTest->addComponent<ModelRenderComponent>()->init("test/mesh_test/teapot.obj");
	guiTest->addComponent<GUITextureRenderComponent>()->init("test/GUItest.png");

	return guiTest;
}

void GOFactory::destroy(GameObject* gameObject) {

	for (unsigned int i = 0; i < m_xProducts.size(); ++i) {

		if (m_xProducts[i] == gameObject) {
		
			if (gameObject->getParent() != nullptr)
				gameObject->getParent()->removeChild(gameObject);

			delete gameObject;
			m_xProducts.erase(m_xProducts.begin() + i);
			return;
		}
	}

	Log::Warn("GOFactory: Trying to destroy unmanaged GameObject");
}

void GOFactory::cleanUp() {

	for (unsigned int i = 0; i < m_xProducts.size(); ++i) {
	
		delete m_xProducts[i];
	}
}
