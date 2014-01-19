#include "SceneLoader.h"

#include "Game.h"
#include "Scene.h"

#include "PerspectiveCameraComponent.h"
#include "ModelRenderComponent.h"
#include "PointLightComponent.h"
#include "MainMenuController.h"

Scene* SceneLoader::fromFile(const char* filepath) {

	m_xFile.open(filepath, std::ios_base::in | std::ios_base::binary);

	if (!m_xFile.is_open()) {

		Log::Err(std::string("Cannot open file: ") + filepath);
		return nullptr;
	}

	Log::Writeln(std::string("Reading scene from file: ") + filepath, Log::COLOR_LIGHT_PURPLE);

	m_xScene = new Scene();

	m_xScene->setAmbientLight(read<glm::vec3>());
	m_xScene->setClearFlags(read<GLuint>());

	readGameObject();

	m_xFile.close();

	return m_xScene;
}

GameObject* SceneLoader::readGameObject() {

	GameObject* go = m_xScene->createEmpty();

	unsigned int size = read<unsigned int>();
	char* name = new char[size+1];

	m_xFile.read(name, size);
	name[size] = 0;

	go->setName(name);

	delete [] name;

	size = read<unsigned int>();
	char* tag = new char[size+1];

	m_xFile.read(tag, size);
	tag[size] = 0;

	go->setTag(tag);

	delete [] tag;

	glm::vec3 position(read<glm::vec3>());
	glm::vec3 scale(read<glm::vec3>());
	glm::quat rotation(read<glm::quat>());

	go->setPosition(position);
	go->setScale(scale);
	go->setRotation(rotation);

	unsigned int num_components = read<unsigned int>();
	unsigned int num_children = read<unsigned int>();

	for (unsigned int i = 0; i < num_components; ++i) {
	
		readComponent(go);
	}

	for (unsigned int i = 0; i < num_children; ++i) {

		go->addChild(readGameObject());
	}

	return go;
}

void SceneLoader::readComponent(GameObject* gameObject) {

	Component::Type type = read<Component::Type>();

	unsigned int creator_name_size = read<unsigned int>();
	char* creator_name = new char[creator_name_size+1];

	m_xFile.read(creator_name, creator_name_size);
	creator_name[creator_name_size] = 0;

	Component* component = gameObject->addComponent(creator_name);

	delete [] creator_name;

	component->accept(this);
}

void SceneLoader::visitScene(Scene* scene) {

}

void SceneLoader::visitGameObject(GameObject* gameObject) {

}

void SceneLoader::visitComponent(Component* component) {

}

void SceneLoader::visitPerspectiveCameraComponent(PerspectiveCameraComponent* component) {

	float fov = read<float>();
	float near = read<float>();
	float far = read<float>();

	glm::ivec2 window_size = Game::instance()->getWindowSize();
	
	component->init(fov, near, far, (float)window_size.x / (float)window_size.y);

	if (m_xScene->getCamera() == nullptr)
		m_xScene->useCamera(component);
}

void SceneLoader::visitModelRenderComponent(ModelRenderComponent* component) {

	unsigned int path_size = read<unsigned int>();
	char* filepath = new char[path_size+1];
	
	m_xFile.read(filepath, path_size);
	filepath[path_size] = 0;

	component->init(filepath);

	delete [] filepath;
}

void SceneLoader::visitPointLightComponent(PointLightComponent* component) {
	
	float radius = read<float>();
	glm::vec3 color = read<glm::vec3>();
	float strength = read<float>();

	component->init(radius, color, strength);
}

void SceneLoader::visitMainMenuController(MainMenuController* component) {

	component->init();
}