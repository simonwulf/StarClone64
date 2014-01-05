#include "stdafx.h"

#include "Scene.h"
#include "LogManager.h"

Scene::Scene() {

	//Test object
	m_xRoot = new GameObject();
	m_xRoot->m_xScene = this;

	m_xCamera = nullptr;
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