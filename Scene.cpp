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