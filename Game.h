#ifndef GAME_H
#define GAME_H

#include "stdafx.h"

#include <iostream>
#include <random>
#include <ctime>

#include "Event.h"
#include "LogManager.h"
#include "Renderer.h"
#include "Scene.h"

class Game : public EventDispatcher {

  public:

	Game();
	~Game();

	int init();

	void loop();
	void quit();

	static Game* instance();

  private:

	static Game* s_xInstance;

	GLFWwindow* m_xWindow;
	Renderer* m_xRenderer;
	Scene* m_xScene;

	GameObject* m_xTestObj;
	GameObject* m_xTestCam;
	GameObject* m_xTestSun;
	GameObject* m_xTestPointLight;
	GameObject* m_xTestPointLight2;

	clock_t m_iLastTime;
	clock_t m_iStartTime;
	float m_fElapsedTime;

	void update(float delta, float elapsedTime);
	void render();
};

#endif