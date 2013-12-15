#include "Scene.h"

Scene::Scene() {

	//Test object
	m_xRoot = new GameObject();
}

Scene::~Scene() {

	delete m_xRoot;
}

GameObject* Scene::getRoot() const {

	return m_xRoot;
}

void Scene::add(GameObject* gameObject) {

	m_xRoot->addChild(gameObject);
}