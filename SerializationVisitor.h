#ifndef SERIALIZATIONVISITOR_H
#define SERIALIZATIONVISITOR_H

#include <fstream>

#include "Visitor.h"

class SerializationVisitor : public Visitor {

  public:

	SerializationVisitor(const char* filepath);

	void close();

	void visitScene(Scene* scene);
	void visitGameObject(GameObject* gameObject);
	void visitComponent(Component* component);

	void visitPerspectiveCameraComponent(PerspectiveCameraComponent* component);
	void visitModelRenderComponent(ModelRenderComponent* component);
	void visitPointLightComponent(PointLightComponent* component);
	void visitMainMenuController(MainMenuController* component);

  private:

	std::ofstream m_xFile;

	template <typename T>
	void write(T data) {
	
		m_xFile.write((char*)&data, sizeof(T));
	}

	void writeText(const char* text);
};

#endif