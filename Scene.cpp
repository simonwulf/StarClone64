#include "Scene.h"

Scene::Scene() {

	//Test object
	m_xRoot = new GameObject();
}

Scene::~Scene() {

}

GameObject* Scene::getRoot() const {

	return m_xRoot;
}