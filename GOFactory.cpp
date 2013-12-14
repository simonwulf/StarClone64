#include "GOFactory.h"

#include "LogManager.h"
#include "ComponentFactory.h"
#include "CameraComponent.h"
#include "RenderComponent.h"
#include "TeapotSpin.h"

GOFactory GOFactory::s_xInstance;

GOFactory::GOFactory() {

}

GOFactory* GOFactory::instance() {

	return &s_xInstance;
}

GameObject* GOFactory::createTeapot() {

	GameObject* teapot = new GameObject();
	teapot->setRotation(glm::angleAxis(-90.0f, 1.0f, 0.0f, 0.0f));
	teapot->addComponent(ComponentFactory::instance()->create<RenderComponent>());
	teapot->addComponent(ComponentFactory::instance()->create<TeapotSpin>());

	m_xProducts.push_back(teapot);

	return teapot;
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