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
#include "CameraController.h"
#include "PerspectiveCameraComponent.h"
#include "OrthographicCameraComponent.h"
#include "GUITextureRenderComponent.h"

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

GameObject* GOFactory::createTestMesh1() {

	GameObject* teapot = createEmpty();
	teapot->addComponent<ModelRenderComponent>()->init("test/mesh_test/boss1/tris.md2");
	return teapot;
}

GameObject* GOFactory::createTestMesh2() {

	GameObject* teapot = createEmpty();
	teapot->addComponent<ModelRenderComponent>()->init("test/mesh_test/boss2/tris.md2");
	return teapot;
}

GameObject* GOFactory::createTestMesh3() {

	GameObject* teapot = createEmpty();
	teapot->addComponent<ModelRenderComponent>()->init("test/mesh_test/teapot.obj");
	return teapot;
}

GameObject* GOFactory::createPlayer() {

	GameObject* player = createEmpty();

	player->addComponent<ModelRenderComponent>()->init("test/mesh_test/teapot.obj");
	player->addComponent<PlayerController>();

	return player;
}

GameObject* GOFactory::createPlayerCamera(GameObject* player, float fov, float near, float far, float ratio) {

	GameObject* camera = createEmpty();

	camera->addComponent<PerspectiveCameraComponent>()->init(fov, near, far, ratio);
	camera->addComponent<CameraController>()->init(player);

	return camera;
}

GameObject* GOFactory::createGUICamera(float width, float height) {

	GameObject* camera = createEmpty();

	camera->addComponent<OrthographicCameraComponent>()->init(0.0f, width, height, 0.0f, -1.0f, 1.0f);

	return camera;
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
	
	PointLightComponent* lightComponent = light->addComponent<PointLightComponent>();
	//light->addComponent(ComponentFactory::instance()->create<RenderComponent>());

	lightComponent->setColor(color);
	lightComponent->setRadius(radius);
	lightComponent->setStrength(strength);

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
