#ifndef VISITOR_H
#define VISITOR_H

class Scene;
class GameObject;
class Component;
class PerspectiveCameraComponent;
class ModelRenderComponent;
class PointLightComponent;
class MainMenuController;

class Visitor {

  public:
	
	virtual void visitScene(Scene* scene) = 0;
	virtual void visitGameObject(GameObject* gameObject) = 0;
	virtual void visitComponent(Component* component) = 0;

	virtual void visitPerspectiveCameraComponent(PerspectiveCameraComponent* component) = 0;
	virtual void visitModelRenderComponent(ModelRenderComponent* component) = 0;
	virtual void visitPointLightComponent(PointLightComponent* component) = 0;
	virtual void visitMainMenuController(MainMenuController* component) = 0;
};

#endif