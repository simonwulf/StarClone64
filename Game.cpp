#include "Game.h"

#include "GOFactory.h"
#include "ComponentFactory.h"

Game* Game::s_xInstance = nullptr;

Game::Game() {

}

Game::~Game() {

	glfwTerminate();

	//delete m_xTestObj;
	delete m_xTestCam;

	GOFactory::instance()->cleanUp();

	delete m_xRenderer;
	delete m_xScene;

	std::cout << "Memory allocated for GameObjects: " << GameObject::getAllocatedMemorySize() << std::endl;
	std::cout << "Memory allocated for Components: " << Component::getAllocatedMemorySize() << std::endl;

	if (GameObject::getAllocatedMemorySize() > 0) {
		
		Log::Warn("All GameObjects have not been deallocated");
	}

	if (Component::getAllocatedMemorySize() > 0) {
		
		Log::Warn("All Components have not been deallocated");
	}
}

int Game::init() {

	glewExperimental = true;
	
	if (!glfwInit()) {
	
		Log::Err("Failed to initialize GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);
	m_xWindow = glfwCreateWindow(1280, 720, "OpenGL Window", NULL/*glfwGetPrimaryMonitor()*/, NULL);
	glfwMakeContextCurrent(m_xWindow);

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
	m_xScene = new Scene();

	//Test purposes
	unsigned int count = 10;
	float dist = 5.0f;
	for (unsigned int z = 0; z < count; ++z) {
		for (unsigned int y = 0; y < count; ++y) {
			for (unsigned int x = 0; x < count; ++x) {
	
				float start = -dist * (float)(count-1)/2.0f;

				GameObject* obj = GOFactory::instance()->createTeapot();
				obj->setPosition(
					glm::vec3(start, start, start) +
					glm::vec3(dist * x, dist * y, dist * z)
				);
				m_xScene->getRoot()->addChild(obj);
			}
		}
	}

	m_xTestCam = new GameObject();
	//m_xTestCam->setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	m_xTestCam->addComponent(ComponentFactory::instance()->create<CameraComponent>());
	m_xScene->add(m_xTestCam);

	/*m_xTestSun = GOFactory::instance()->createSun(
		glm::vec3(-0.5f, -1.0f, -0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		1.0f
	);
	m_xScene->add(m_xTestSun);*/

	m_xTestPointLight = GOFactory::instance()->createPointLight(
		glm::vec3(0.0f, 0.5f, 1.0f),
		12.0f,
		1.0f
	);
	m_xScene->add(m_xTestPointLight);

	m_xTestPointLight2 = GOFactory::instance()->createPointLight(
		glm::vec3(1.0f, 0.0f, 0.5f),
		12.0f,
		1.0f
	);
	m_xScene->add(m_xTestPointLight2);

	float hue = 0.0f;
	float r, g, b;

	for (unsigned int i = 0; i < 62; ++i) {

		if (hue < 60.0f) {
		
			r = 1.0f;
			g = hue / 60.0f;
			b = 0.0f;
		
		} else if (hue < 120.0f) {
		
			r = 1.0f - ((hue-60.0f) / 60.0f);
			g = 1.0f;
			b = 0.0f;
		
		} else if (hue < 180.0f) {
		
			r = 0.0f;
			g = 1.0f;
			b = (hue - 120.0f) / 60.0f;

		} else if (hue < 240.0f) {
		
			r = 0.0f;
			g = 1.0f - ((hue - 180.0f) / 60.0f);
			b = 1.0f;

		} else if (hue < 300.0f) {
		
			r = (hue - 240.0f) / 60.0f;
			g = 0.0f;
			b = 1.0f;

		} else {
		
			r = 1.0f;
			g = 0.0f;
			b = 1.0f - ((hue - 300.0f) / 60.0f);
		}

		hue += 360.0f / 62.0f;

		GameObject* pl = GOFactory::instance()->createPointLight(
			glm::vec3(r, g, b),
			8.0f,
			1.0f
		);
		m_xScene->add(pl);
	}

	std::cout << "Memory allocated for GameObjects: " << GameObject::getAllocatedMemorySize() << std::endl;
	std::cout << "Memory allocated for Components: " << Component::getAllocatedMemorySize() << std::endl;
}

void Game::loop() {

	m_iLastTime = m_iStartTime = clock();
	m_fElapsedTime = 0.0f;
	float delta = 0.0f;

	while(!glfwWindowShouldClose(m_xRenderer->getWindow())) {
	
		glfwPollEvents();

		update(delta, m_fElapsedTime);
		m_xRenderer->render(m_xScene);

		clock_t now = clock();
		delta = (float)(now - m_iLastTime) / (float)CLOCKS_PER_SEC;
		if (delta > 0.1f)
			delta = 0.1f;
		m_fElapsedTime += delta;
		m_iLastTime = now;
	}
}

void Game::update(float delta, float elapsedTime) {

	ComponentFactory::instance()->update(Component::CONTROLLER, delta, elapsedTime);

	/* *
	m_xTestCam->setRotation(glm::angleAxis(
		elapsedTime * 30.0f,
		glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))
	));
	/* */

	/*m_xTestPointLight->setPosition(glm::vec3(
		cosf(elapsedTime * 2.0f) * 8.0f,
		sinf(elapsedTime * 2.0f) * 8.0f,
		0.0f
	));

	m_xTestPointLight2->setPosition(glm::vec3(
		0.0f,
		0.0f,
		cosf(elapsedTime) * 20.0f
	));*/

	if (elapsedTime >= 3.0f && elapsedTime < 40.0f)
		m_xTestCam->setPosition(glm::vec3(0.0f, 0.0f, 1.0f) * (elapsedTime - 3.0f));
}