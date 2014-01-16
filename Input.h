#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "EventDispatcher.h"

class Input : public EventDispatcher {

  public:

	void init(GLFWwindow* window);
	void update();

	bool isJoyPluggedIn();

	static Input* instance();

  private:

	Input();
	~Input();
	Input(const Input&);

	static Input s_xInstance;

	bool m_bJoyPresent;
	int m_iNumJoyButtons;
	bool* m_bJoyButtons;
	int m_iNumJoyAxes;
	float* m_fJoyAxes;

	void joyPluggedIn();
	void joyPluggedOut();
};

#endif