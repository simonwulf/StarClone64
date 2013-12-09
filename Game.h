#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GL/wglew.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
#include <glext.h>
#include <wglext.h>
#include <iostream>
#include <ctime>
#include <Windows.h>

#include "LogManager.h"
#include "Renderer.h"
#include "Scene.h"

class Game {

  public:

	Game();
	~Game();

	int init();

	void loop();

  private:

	static const unsigned int TARGET_FPS = 60;

	GLFWwindow* m_xWindow;
	Renderer* m_xRenderer;
	Scene* m_xScene;

	clock_t m_iLastTime;
	clock_t m_iStartTime;
	float m_fElapsedTime;

	void update(float delta, float elapsedTime);
	void render();
};

#endif