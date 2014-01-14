#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "GameObject.h"

#undef near
#undef far

class Player : public GameObject {
public: void init();
};

class Laser : public GameObject {
public: void init();
};

class SmallEnemy : public GameObject {
public: void init();
};

class SimpleModel : public GameObject {
public: void init(const char* modelPath);
};

class Skybox : public GameObject {
public: void init();
};

class PlayerCamera : public GameObject {
public: void init(GameObject* player, float fov, float near, float far, float ratio);
};

class SkyCamera : public GameObject {
public: void init(GameObject* refObj, float fov, float near, float far, float ratio);
};

class GUICamera : public GameObject {
public: void init(float width, float height);
};

class GUITexture : public GameObject {
public: void init(const char* texturePath);
};

class Sun : public GameObject {
public: void init(glm::vec3 direction, glm::vec3 color, float strength);
};

class PointLight : public GameObject {
public: void init(glm::vec3 color, float radius, float strength);
};

class MainMenu : public GameObject {
public: void init();
};

#endif