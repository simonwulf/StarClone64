#include "Game.h"

#include "Input.h"
#include "CollisionManager.h"

#include "PlayScene.h"
#include "HUDScene.h"
#include "SkyScene.h"
#include "MenuGUIScene.h"
#include "Menu3DScene.h"


Game* Game::s_xInstance = nullptr;

Game::Game() {

	if (s_xInstance != nullptr)
		throw std::exception("Singleton class Game has already been instantiated");

	s_xInstance = this;

	m_fElapsedTime = 0.0f;
	m_fTimeScale = 1.0f;

	m_iState = (State)-1;
}

Game::~Game() {

	glfwTerminate();

	delete m_xRenderer;

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		delete m_xScenes[i];
	}

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
	/* *
	int monitor_count;
	GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
	m_xWindow = glfwCreateWindow(1920, 1080, "OpenGL Window", monitor_count > 1 ? monitors[1] : monitors[0], nullptr);
	/* */
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
	
	m_xPlayScene = new PlayScene();
	m_xSkyScene = new SkyScene();
	static_cast<SkyScene*>(m_xSkyScene)->init(m_xPlayScene->getCamera()->getGameObject());
	m_xSkyScene->setVisible(true);
	m_xHUDScene = new HUDScene();
	m_xMenuGUIScene = new MenuGUIScene();
	//m_xMenu3DScene = new Menu3DScene();

	m_xScenes.push_back(m_xSkyScene);
	m_xScenes.push_back(m_xPlayScene);
	m_xScenes.push_back(m_xHUDScene);
	m_xScenes.push_back(m_xMenuGUIScene);
	//m_xScenes.push_back(m_xMenu3DScene);

	Input::instance()->init(m_xWindow);

	std::cout << "Memory allocated for GameObjects: " << GameObject::getAllocatedMemorySize() << std::endl;
	std::cout << "Memory allocated for Components: " << Component::getAllocatedMemorySize() << std::endl;

	setState(MENU_STATE);

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
		render();

		clock_t now = clock();
		delta = ((float)(now - m_iLastTime) / (float)CLOCKS_PER_SEC) * m_fTimeScale;
		m_fElapsedTime += delta;
		m_iLastTime = now;
	}
}

void Game::quit() {

	glfwSetWindowShouldClose(m_xWindow, true);
}

void Game::pause() {

	if (m_iState != PAUSE_STATE)
		setState(PAUSE_STATE);
	else
		setState(PLAY_STATE);
}

//Using a very decentralised, event based approach to game states.
//Gameobjects are free to react to state changes any way they like.
void Game::setState(State state) {

	if ((int)m_iState != -1)
		leaveState(m_iState);
		//dispatchEvent(makeGameEvent(Event::GAME_LEAVE_STATE));

	m_iState = state;

	enterState(m_iState);
	//dispatchEvent(makeGameEvent(Event::GAME_ENTER_STATE));
}

Game::State Game::getState() const {

	return m_iState;
}

void Game::enterState(State state) {

	std::cout << __FUNCTION__ << ": " << state << std::endl;

	switch (state) {
	
		case MENU_STATE:
			m_xMenuGUIScene->setActive(true);
			m_xMenuGUIScene->setVisible(true);
			break;

		case PLAY_STATE:
			m_xSkyScene->setActive(true);
			m_xPlayScene->setActive(true);
			m_xPlayScene->setVisible(true);
			m_xHUDScene->setActive(true);
			m_xHUDScene->setVisible(true);
			break;

		case PAUSE_STATE:
			m_xPlayScene->setActive(false);
			m_xPlayScene->setVisible(true);
			m_xMenuGUIScene->setActive(true);
			m_xMenuGUIScene->setVisible(true);
			break;
	}
}

void Game::leaveState(State state) {

	switch (state) {
	
		case MENU_STATE:
			m_xMenuGUIScene->setActive(false);
			m_xMenuGUIScene->setVisible(false);
			break;

		case PLAY_STATE:
			m_xSkyScene->setActive(false);
			m_xPlayScene->setActive(false);
			m_xPlayScene->setVisible(false);
			m_xHUDScene->setActive(false);
			m_xHUDScene->setVisible(false);
			break;

		case PAUSE_STATE:
			m_xPlayScene->setActive(true);
			m_xPlayScene->setVisible(false);
			m_xMenuGUIScene->setActive(false);
			m_xMenuGUIScene->setVisible(false);
			break;
	}
}

void Game::update(float delta, float elapsedTime) {

	/*Event e = makeGameEvent(Event::GAME_UPDATE);
	e.game.delta = delta;

	dispatchEvent(e);*/

	Input::instance()->update();

	/*switch (m_iState) {
	
		case Game::PAUSE_STATE:
		case Game::MENU_STATE:
			m_xHUDScene->update(delta, elapsedTime);
			break;

		case Game::PLAY_STATE:
			m_xSkyScene->update(delta, elapsedTime);
			m_xPlayScene->update(delta, elapsedTime);
			m_xHUDScene->update(delta, elapsedTime);

			CollisionManager::checkCollisions(m_xPlayScene);

			m_xSkyScene->lateUpdate(delta, elapsedTime);
			m_xPlayScene->lateUpdate(delta, elapsedTime);
			m_xHUDScene->lateUpdate(delta, elapsedTime);
			break;
	}*/

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isActive())
			m_xScenes[i]->update(delta, elapsedTime);
	}

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isActive())
			CollisionManager::checkCollisions(m_xScenes[i]);
	}

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isActive())
			m_xScenes[i]->lateUpdate(delta, elapsedTime);
	}

	/*e.type = Event::GAME_UPDATE_LATE;
	dispatchEvent(e);*/

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isActive())
			m_xScenes[i]->removeDead();
	}

	//m_xSkyScene->removeDead();
	//m_xPlayScene->removeDead();
	//m_xHUDScene->removeDead();
}

void Game::render() {

 	/*m_xRenderer->render(m_xSkyScene);
// 	m_xRenderer->render(m_xPlayScene);
// 	m_xRenderer->render(m_xHUDScene);
	m_xRenderer->render(m_xMenu3DScene);
	m_xRenderer->render(m_xMenuGUIScene);*/

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isVisible())
			m_xRenderer->render(m_xScenes[i]);
	}

	glfwSwapBuffers(m_xWindow);
}

Event Game::makeGameEvent(Event::Type type) {

	Event e(type);
	e.game.delta = 0.0f;
	e.game.elapsedTime = m_fElapsedTime;
	e.game.state = m_iState;

	return e;
}

const glm::ivec2& Game::getWindowSize() const {

	return m_vWindowSize;
}