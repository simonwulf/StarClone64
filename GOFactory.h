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
	GameObject* createTestMesh1();
	GameObject* createTestMesh2();
	GameObject* createTestMesh3();
	GameObject* createPlayer();
	GameObject* createPlayerCamera(GameObject* player, float fov, float near, float far, float ratio);
	GameObject* createGUICamera(float width, float height);
	GameObject* createSun(glm::vec3 direction, glm::vec3 color, float strength);
	GameObject* createPointLight(glm::vec3 color, float radius, float strength);
	GameObject* createGUITest();

	void destroy(GameObject* gameObject);

	static GOFactory* instance();

  private:

	static GOFactory s_xInstance;

	GOFactory();

	std::vector<GameObject*> m_xProducts;
};

#endif