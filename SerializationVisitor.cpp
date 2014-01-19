#include "SerializationVisitor.h"

#include <string.h>

#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "PerspectiveCameraComponent.h"
#include "ModelRenderComponent.h"
#include "PointLightComponent.h"
#include "MainMenuController.h"
#include "Model.h"
#include "LogManager.h"

#undef near
#undef far

SerializationVisitor::SerializationVisitor(const char* filepath) : m_xFile(filepath, std::ios_base::binary | std::ios_base::trunc) {

	if (!m_xFile.is_open())
		Log::Err(std::string("Could not open file for serialization: ") + filepath);
}

void SerializationVisitor::close() {

	m_xFile.close();
}

void SerializationVisitor::visitScene(Scene* scene) {

	write(scene->getAmbientLight());
	write(scene->getClearFlags());
}

void SerializationVisitor::visitGameObject(GameObject* gameObject) {

	std::string name = gameObject->getName();
	std::string tag = gameObject->getTag();

	writeText(name.c_str());
	writeText(tag.c_str());

	write(gameObject->getPosition());
	write(gameObject->getScale());
	write(gameObject->getRotation());
	write(gameObject->numComponents());
	write(gameObject->numChildren());
}

void SerializationVisitor::visitComponent(Component* component) {

	write(component->getType());
}

void SerializationVisitor::visitPerspectiveCameraComponent(PerspectiveCameraComponent* component) {

	visitComponent(component);
	writeText("perspective_camera");

	write(component->getFov());
	write(component->getNear());
	write(component->getFar());
}

void SerializationVisitor::visitModelRenderComponent(ModelRenderComponent* component) {

	visitComponent(component);
	writeText("model_render");

	std::string path = component->getModel()->getPath();

	write(path.size());
	m_xFile.write(path.c_str(), path.size());
}

void SerializationVisitor::visitPointLightComponent(PointLightComponent* component) {
	
	visitComponent(component);
	writeText("point_light");

	write(component->getRadius());
	write(component->getColor());
	write(component->getStrength());
}

void SerializationVisitor::visitMainMenuController(MainMenuController* component) {

	visitComponent(component);
	writeText("main_menu_controller");
}

void SerializationVisitor::writeText(const char* text) {

	unsigned int length = strlen(text);
	m_xFile.write((char*)&length, sizeof(unsigned int));
	m_xFile.write(text, length);
}