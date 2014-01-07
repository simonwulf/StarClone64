#include "stdafx.h"

#include "Scene.h"
#include "LogManager.h"

Scene::Scene() {

	//Test object
	m_xRoot = new GameObject();
	m_xRoot->m_xScene = this;

	m_xCamera = nullptr;

	m_iClearFlags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
}

Scene::~Scene() {

	delete m_xRoot;
}

GameObject* Scene::getRoot() {

	return m_xRoot;
}

void Scene::add(GameObject* gameObject) {

	m_xRoot->addChild(gameObject);
}

void Scene::useCamera(CameraComponent* camera) {

	if (camera->getGameObject()->getScene() != this) {
	
		Log::Warn("A camera can only be used with the scene it is part of");
		return;
	}

	m_xCamera = camera;
}

const CameraComponent* Scene::getCamera() const {

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