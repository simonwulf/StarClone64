#include "Game.h"

#include "Input.h"
#include "GOFactory.h"

#include "PlayScene.h"
#include "HUDScene.h"
#include "SkyScene.h"

Game* Game::s_xInstance = nullptr;

Game::Game() {

	if (s_xInstance != nullptr)
		throw std::exception("Singleton class Game has already been instantiated");

	s_xInstance = this;

	m_iState = (State)-1;
}

Game::~Game() {

	glfwTerminate();

	GOFactory::instance()->cleanUp();

	delete m_xRenderer;
	delete m_xPlayScene;
	delete m_xHUDScene;
	delete m_xSkyScene;

	std::cout << "Memory allocated for GameObjects: " << GameObject::getAllocatedMemorySize() << std::endl;
	std::cout << "Memory allocated for Components: " << Component::getAllocatedMemorySize() << std::endl;

	if (GameObject::getAllocatedMemorySize() > 0) {
		
		Log::Warn("All GameObjects have not been deallocated");
	}

	if (Component::getAllocatedMemorySize() > 0) {
		
		Log::Warn("All Components have not been deallocated");
	}
}

Game* Game::instance() {

	return s_xInstance;
}

int Game::init() {

	glewExperimental = true;
	
	if (!glfwInit()) {
	
		Log::Err("Failed to initialize GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);
	//m_xWindow = glfwCreateWindow(1920, 1080, "OpenGL Window", glfwGetPrimaryMonitor(), nullptr);
	m_xWindow = glfwCreateWindow(1280, 720, "OpenGL Window", nullptr, nullptr);
	glfwMakeContextCurrent(m_xWindow);

	glfwGetWindowSize(m_xWindow, &m_vWindowSize.x, &m_vWindowSize.y);

	int MajorVersion;
	int MinorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);

	std::cout << "OpenGL v" << MajorVersion << "." << MinorVersion << std::endl;

	if(glewInit() != GLEW_OK) {

		Log::Err("Failed to initialize GLEW");
		return -1;
	}

	std::cout << "GLEW version " << glewGetString(GLEW_VERSION) << "\n";

	m_xRenderer = new Renderer(m_xWindow);
	
	m_xSkyScene = new SkyScene();
	m_xPlayScene = new PlayScene();
	((SkyScene*) m_xSkyScene)->init(m_xPlayScene->getCamera()->getGameObject());
	m_xHUDScene = new HUDScene();

	Input::instance()->init(m_xWindow);

	std::cout << "Memory allocated for GameObjects: " << GameObject::getAllocatedMemorySize() << std::endl;
	std::cout << "Memory allocated for Components: " << Component::getAllocatedMemorySize() << std::endl;

	setState(PLAY_STATE);

	return 0;
}

void Game::loop() {

	m_iLastTime = m_iStartTime = clock();
	m_fElapsedTime = 0.0f;
	float delta = 0.0f;

	dispatchEvent(Event(Event::GAME_START));

	while(!glfwWindowShouldClose(m_xRenderer->getWindow())) {
	
		glfwPollEvents();

		update(delta, m_fElapsedTime);
		dispatchEvent(makeGameEvent(Event::GAME_UPDATE_LATE));
		render();

		clock_t now = clock();
		delta = (float)(now - m_iLastTime) / (float)CLOCKS_PER_SEC;
		if (delta > 0.1f)
			delta = 0.1f;
		m_fElapsedTime += delta;
		m_iLastTime = now;
	}
}

void Game::quit() {

	glfwSetWindowShouldClose(m_xWindow, true);
}

//Using a very decentralised, event based approach to game states.
//Gameobjects are free to react to state changes any way they like.
void Game::setState(State state) {

	if ((int)m_iState != -1)
		dispatchEvent(makeGameEvent(Event::GAME_LEAVE_STATE));

	m_iState = state;

	dispatchEvent(makeGameEvent(Event::GAME_ENTER_STATE));
}

void Game::update(float delta, float elapsedTime) {

	Event e = makeGameEvent(Event::GAME_UPDATE);
	e.game.delta = delta;

	dispatchEvent(e);
}

void Game::render() {

	m_xRenderer->render(m_xSkyScene);
	m_xRenderer->render(m_xPlayScene);
	m_xRenderer->render(m_xHUDScene);

	glfwSwapBuffers(m_xWindow);
}

Event& Game::makeGameEvent(Event::Type type) {

	Event e(type);
	e.game.delta = 0.0f;
	e.game.elapsedTime = m_fElapsedTime;
	e.game.state = m_iState;

	return e;
}

const glm::ivec2& Game::getWindowSize() const {

	return m_vWindowSize;
}