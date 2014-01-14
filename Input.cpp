#include "stdafx.h"

#include "Input.h"
#include "Game.h"
#include "LogManager.h"

#pragma region glfw_callbacks

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE)
		Game::instance()->quit();

	Event e((Event::Type)-1);

	switch (action) {

		case GLFW_RELEASE:
			e.type = Event::KEY_UP;
			break;

		case GLFW_PRESS:
			
			e.type = Event::KEY_DOWN;
			break;

		case GLFW_REPEAT:
			return;
	}

	e.keyboard.charCode = key;
	e.keyboard.keyCode = scancode;

	Input::instance()->dispatchEvent(e);
}

#pragma endregion glfw_callbacks

Input Input::s_xInstance;

Input::Input() {

	m_bJoyButtons = nullptr;
	m_fJoyAxes = nullptr;
	m_bJoyPresent = false;
}

Input::~Input() {

	if (m_fJoyAxes != nullptr)
		delete [] m_fJoyAxes;

	if (m_bJoyButtons != nullptr)
		delete [] m_bJoyButtons;
}

Input* Input::instance() {

	return &s_xInstance;
}

void Input::init(GLFWwindow* window) {

	glfwSetKeyCallback(window, keyCallback);

	if (m_bJoyPresent = glfwJoystickPresent(0))
		joyPluggedIn();
}

void Input::update() {
	
	if (m_bJoyPresent && !glfwJoystickPresent(0)) {
		
		joyPluggedOut();
		return;
	
	} else if (!m_bJoyPresent && glfwJoystickPresent(0)) {
	
		joyPluggedIn();
		return;
	
	} else if (!m_bJoyPresent) {
	
		return;
	}

	const float* axes = glfwGetJoystickAxes(0, &m_iNumJoyAxes);
	const unsigned char* buttons = glfwGetJoystickButtons(0, &m_iNumJoyButtons);

	for (int i = 0; i < m_iNumJoyAxes; ++i) {
	
		if (m_fJoyAxes[i] != axes[i]) {
		
			Event e(Event::JOY_AXIS_CHANGE);

			e.joypad.joypad = 0;
			e.joypad.button = -1;
			e.joypad.axis = i;
			e.joypad.axisValue = axes[i];

			dispatchEvent(e);
		}

		m_fJoyAxes[i] = axes[i];
	}

	for (int i = 0; i < m_iNumJoyButtons; ++i) {
	
		if (m_bJoyButtons[i] != (bool)buttons[i]) {
		
			Event e(buttons[i] ? Event::JOY_BUTTON_DOWN : Event::JOY_BUTTON_UP);

			e.joypad.joypad = 0;
			e.joypad.button = i;
			e.joypad.axis = -1;
			e.joypad.axisValue = 0.0f;

			dispatchEvent(e);
		}

		m_bJoyButtons[i] = buttons[i];
	}
}

void Input::joyPluggedIn() {

	m_bJoyPresent = true;

	const float* axes = glfwGetJoystickAxes(0, &m_iNumJoyAxes);
	const unsigned char* buttons = glfwGetJoystickButtons(0, &m_iNumJoyButtons);

	m_fJoyAxes = new float[m_iNumJoyAxes];
	memcpy(m_fJoyAxes, axes, sizeof(float) * m_iNumJoyAxes);

	m_bJoyButtons = new bool[m_iNumJoyButtons];
	for (int i = 0; i < m_iNumJoyButtons; ++i) {
	
		m_bJoyButtons[i] = buttons[i];
	}

	Event e(Event::JOY_PLUGGED_IN);
	e.joypad.joypad = 0;
	e.joypad.button = -1;
	e.joypad.axis = -1;
	e.joypad.axisValue = 0.0f;

	dispatchEvent(e);

	Log::Writeln(std::string("Joypad plugged in: ") + glfwGetJoystickName(0), Log::COLOR_LIGHT_AQUA);
	//Log::Writeln(std::string("Number of axes: " + m_iNumJoyAxes));
	std::cout << "Number of axes: " << m_iNumJoyAxes << std::endl;
	std::cout << "Number of buttons: " << m_iNumJoyButtons << std::endl;
}

void Input::joyPluggedOut() {

	m_bJoyPresent = false;

	delete [] m_fJoyAxes;
	m_fJoyAxes = nullptr;

	delete [] m_bJoyButtons;
	m_bJoyButtons = nullptr;

	Event e(Event::JOY_PLUGGED_OUT);
	e.joypad.joypad = 0;
	e.joypad.button = -1;
	e.joypad.axis = -1;
	e.joypad.axisValue = 0.0f;

	dispatchEvent(e);

	Log::Writeln("Joypad disconnected", Log::COLOR_LIGHT_YELLOW);
}