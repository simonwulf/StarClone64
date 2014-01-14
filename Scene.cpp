#include "stdafx.h"

#include "Game.h"
#include "Scene.h"
#include "LogManager.h"

#include "CameraComponent.h"
#include "CollisionManager.h"
#include "Input.h"

#define FUNC_MESSAGE(msg) std::string(__FUNCTION__) + ": " + msg

Scene::Scene() {

	//Test object
	m_xRoot = new GameObject();
	m_xRoot->m_xScene = this;

	m_xCamera = nullptr;

	m_iClearFlags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

	Input::instance()->registerEventHandler(Event::KEY_DOWN, this, &Scene::inputHandler);
	Input::instance()->registerEventHandler(Event::KEY_UP, this, &Scene::inputHandler);
	Input::instance()->registerEventHandler(Event::JOY_AXIS_CHANGE, this, &Scene::inputHandler);
	Input::instance()->registerEventHandler(Event::JOY_BUTTON_DOWN, this, &Scene::inputHandler);
	Input::instance()->registerEventHandler(Event::JOY_BUTTON_UP, this, &Scene::inputHandler);

	m_bActive = false;
	m_bVisible = false;
}

Scene::~Scene() {

	for (unsigned int i = 0; i < m_xGameObjects.size(); ++i) {
	
		delete m_xGameObjects[i];
	}

	m_xGameObjects.clear();

	delete m_xRoot;

	Input::instance()->removeEventHandler(Event::KEY_DOWN, this, &Scene::inputHandler);
	Input::instance()->removeEventHandler(Event::KEY_UP, this, &Scene::inputHandler);
	Input::instance()->removeEventHandler(Event::JOY_AXIS_CHANGE, this, &Scene::inputHandler);
	Input::instance()->removeEventHandler(Event::JOY_BUTTON_DOWN, this, &Scene::inputHandler);
	Input::instance()->removeEventHandler(Event::JOY_BUTTON_UP, this, &Scene::inputHandler);
}

/*GameObject* Scene::getRoot() {

	return m_xRoot;
}

void Scene::add(GameObject* gameObject) {

	m_xRoot->addChild(gameObject);
}*/

void Scene::update(float delta, float elapsedTime) {

	Event e(Event::GAME_UPDATE);
	e.game.delta = delta;
	e.game.elapsedTime = elapsedTime;
	e.game.state = Game::instance()->getState();

	dispatchEvent(e);
}

void Scene::lateUpdate(float delta, float elapsedTime) {

	Event e(Event::GAME_UPDATE_LATE);
	e.game.delta = delta;
	e.game.elapsedTime = elapsedTime;
	e.game.state = Game::instance()->getState();

	dispatchEvent(e);
}

GameObject* Scene::make(const std::string& type) {

	return make<GameObject>(type);
}

void Scene::removeDead() {

	removeDead_r(m_xRoot);
}

void Scene::removeDead_r(GameObject* node) {

	for (unsigned int i = 0; i < node->numChildren(); ++i) {
	
		removeDead_r(node->childAt(i));
	}

	if (!node->m_bDead)
		return;

	if (node->getParent() != nullptr)
		node->getParent()->removeChild(node);

	for (unsigned int i = 0; i < m_xGameObjects.size(); ++i) {
		if (m_xGameObjects[i] == node) {
		
			m_xGameObjects.erase(m_xGameObjects.begin() + i);
			break;
		}
	}

	delete node;
}

void Scene::registerComponent(Component* component) {

	if (component->getGameObject()->getScene() != this) {
		
		Log::Err(FUNC_MESSAGE("A Component can only be registered in the Scene that contains it's GameObject"));
		return;
	}

	m_xComponents[component->getType()].push_back(component);
}

void Scene::removeComponent(Component* component) {

	if (component->getGameObject()->getScene() != this) {
		
		Log::Err(FUNC_MESSAGE("A Component can only be removed from the Scene that contains it's GameObject"));
		return;
	}

	ComponentList& list = m_xComponents[component->getType()];

	for (unsigned int i = 0; i < list.size(); ++i) {
	
		if (list[i] == component) {
		
			list.erase(list.begin() + i);
			return;
		}
	}

	Log::Warn(FUNC_MESSAGE("Component not found"));
}

void Scene::useCamera(CameraComponent* camera) {

	if (camera->getGameObject()->getScene() != this) {
	
		Log::Err(FUNC_MESSAGE("A camera can only be used with the scene it is part of"));
		return;
	}

	m_xCamera = camera;
}

CameraComponent* Scene::getCamera() {

	return m_xCamera;
}

GLuint Scene::getClearFlags() const {

	return m_iClearFlags;
}

void Scene::setClearFlags(GLuint flags) {

	m_iClearFlags = flags;
}

const glm::vec3& Scene::getAmbientLight() const {

	return m_vAmbientLight;
}

void Scene::setAmbientLight(const glm::vec3& light) {

	m_vAmbientLight = light;
}

Scene::ComponentList* Scene::getComponents(Component::Type type) {

	return &m_xComponents[type];
}

RaycastResult Scene::raycast(Ray ray) {

	return CollisionManager::raycast(ray, this);
}

void Scene::setActive(bool active) {

	m_bActive = active;
}

bool Scene::isActive() const {

	return m_bActive;
}

void Scene::setVisible(bool visible) {

	m_bVisible = visible;
}

bool Scene::isVisible() const {

	return m_bVisible;
}

void Scene::inputHandler(const Event& e) {

	if (m_bActive)
		dispatchEvent(e);
}