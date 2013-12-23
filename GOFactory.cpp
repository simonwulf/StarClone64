#include "GOFactory.h"

#include "LogManager.h"
#include "ComponentFactory.h"
#include "CameraComponent.h"
#include "RenderComponent.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "TeapotSpin.h"
#include "RandomMover.h"
#include "PlayerController.h"

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
	teapot->setRotation(glm::angleAxis(-90.0f, 1.0f, 0.0f, 0.0f));
	teapot->addComponent(ComponentFactory::instance()->create<RenderComponent>());
	teapot->addComponent(ComponentFactory::instance()->create<TeapotSpin>());

	//teapot->addComponent(ComponentFactory::instance()->create<RandomMover>());

	return teapot;
}

GameObject* GOFactory::createPlayer() {

	GameObject* player = createEmpty();

	player->addComponent(ComponentFactory::instance()->create<RenderComponent>());
	player->addComponent(ComponentFactory::instance()->create<PlayerController>());

	return player;
}

GameObject* GOFactory::createSun(glm::vec3 direction, glm::vec3 color, float strength) {

	GameObject* sun = createEmpty();
	
	DirectionalLightComponent* lightComponent = (DirectionalLightComponent*)ComponentFactory::instance()->create<DirectionalLightComponent>();
	sun->addComponent(lightComponent);

	lightComponent->setDirection(direction);
	lightComponent->setColor(color);
	lightComponent->setStrength(strength);

	return sun;
}

GameObject* GOFactory::createPointLight(glm::vec3 color, float radius, float strength) {

	GameObject* light = createEmpty();
	
	PointLightComponent* lightComponent = (PointLightComponent*)ComponentFactory::instance()->create<PointLightComponent>();
	light->addComponent(lightComponent);
	//light->addComponent(ComponentFactory::instance()->create<RenderComponent>());

	lightComponent->setColor(color);
	lightComponent->setRadius(radius);
	lightComponent->setStrength(strength);

	light->addComponent(ComponentFactory::instance()->create<RandomMover>());

	return light;
}

/*GameObject* GOFactory::createControlledCamera() {

	GameObject* camera = new GameObject();
	camera->addComponent(ComponentFactory::instance()->create<CameraComponent>());
	
	m_xProducts.push_back(camera);
}*/

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