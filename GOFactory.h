#ifndef GOFACTORY_H
#define GOFACTORY_H

#include <vector>

#include "GameObject.h"

class GOFactory {

  public:

	void cleanUp();

	GameObject* createTeapot();
	//GameObject* createControlledCamera();
	
	void destroy(GameObject* gameObject);

	static GOFactory* instance();

  private:

	static GOFactory s_xInstance;

	GOFactory();

	std::vector<GameObject*> m_xProducts;
};

#endif