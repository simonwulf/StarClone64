#ifndef GOFACTORY_H
#define GOFACTORY_H

#include <vector>

#include "GameObject.h"

class GOFactory {

  public:

	void cleanUp();

	GameObject* createEmpty();
	GameObject* createTeapot();
	GameObject* createSun(glm::vec3 direction, glm::vec3 color, float strength);
	GameObject* createPointLight(glm::vec3 color, float radius, float strength);
	//GameObject* createControlledCamera();
	
	void destroy(GameObject* gameObject);

	static GOFactory* instance();

  private:

	static GOFactory s_xInstance;

	GOFactory();

	std::vector<GameObject*> m_xProducts;
};

#endif