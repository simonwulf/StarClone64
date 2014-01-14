#ifndef GOFACTORY_H
#define GOFACTORY_H

#include <vector>

#include "GameObject.h"

#undef near
#undef far

class GOFactory {

  public:

	void cleanUp();

	GameObject* createEmpty();
	GameObject* createTeapot();
	GameObject* createLaser();
	GameObject* createPlayer();
	GameObject* createSkybox();
	GameObject* createPlayerCamera(GameObject* player, float fov, float near, float far, float ratio);
	GameObject* createGUICamera(float width, float height);
	GameObject* createSkyCamera(GameObject* refObj, float fov, float near, float far, float ratio);
	GameObject* createGroundPlane();
	GameObject* createSun(glm::vec3 direction, glm::vec3 color, float strength);
	GameObject* createPointLight(glm::vec3 color, float radius, float strength);
	GameObject* createGUITest();
	GameObject* createMainMenu();

	void destroy(GameObject* gameObject);

	static GOFactory* instance();

  private:

	static GOFactory s_xInstance;

	GOFactory();

	std::vector<GameObject*> m_xProducts;
};

#endif