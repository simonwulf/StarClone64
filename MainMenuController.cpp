#include "MainMenuController.h"
#include "GOFactory.h"
#include "Scene.h"
#include "Input.h"
#include "Game.h"
#include "Visitor.h"

MainMenuController::MainMenuController() {

	index = 0;
	m_iJoyDirection = 0;
}

MainMenuController::~MainMenuController() {

	m_xGameObject->getScene()->removeEventHandler(Event::GAME_START, this, &MainMenuController::start);
	m_xGameObject->getScene()->removeEventHandler(Event::KEY_DOWN, this, &MainMenuController::keyDownHandler);
	m_xGameObject->getScene()->removeEventHandler(Event::JOY_AXIS_CHANGE, this, &MainMenuController::axisChangeHandler);
	m_xGameObject->getScene()->removeEventHandler(Event::JOY_BUTTON_DOWN, this, &MainMenuController::buttonDownHandler);
}

void MainMenuController::init() {

	m_xGameObject->getScene()->registerEventHandler(Event::GAME_START, this, &MainMenuController::start);
	m_xGameObject->getScene()->registerEventHandler(Event::KEY_DOWN, this, &MainMenuController::keyDownHandler);
	m_xGameObject->getScene()->registerEventHandler(Event::JOY_AXIS_CHANGE, this, &MainMenuController::axisChangeHandler);
	m_xGameObject->getScene()->registerEventHandler(Event::JOY_BUTTON_DOWN, this, &MainMenuController::buttonDownHandler);
}

void MainMenuController::accept(Visitor* visitor) {

	visitor->visitMainMenuController(this);
}

void MainMenuController::updateMenu() {

	switch(index) {
		case 0:
			m_xStart->getModel()->getMeshes()[0].setMaterial(m_xMatSelected);
			m_xQuit->getModel()->getMeshes()[0].setMaterial(m_xMatDeselected);
			break;
		case 1:
			m_xStart->getModel()->getMeshes()[0].setMaterial(m_xMatDeselected);
			m_xQuit->getModel()->getMeshes()[0].setMaterial(m_xMatSelected);
			break;
	}
}

void MainMenuController::step(int steps) {

	index = (index + steps) % 2;

	updateMenu();
}

void MainMenuController::select() {

	switch(index) {
		case 0: Game::instance()->setState(Game::PLAY_STATE); break;
		case 1: Game::instance()->quit(); break;
	}
}

void MainMenuController::start(const Event& e) {

	GameObject* startItem = m_xGameObject->find("item_start");
	GameObject* quitItem = m_xGameObject->find("item_quit");

	m_xStart = static_cast<ModelRenderComponent*>(startItem->getComponent(Component::RENDER));
	m_xQuit = static_cast<ModelRenderComponent*>(quitItem->getComponent(Component::RENDER));

	m_xMatSelected = m_xStart->getModel()->getMeshes()[0].getMaterial();
	m_xMatDeselected = m_xQuit->getModel()->getMeshes()[0].getMaterial();
}

void MainMenuController::keyDownHandler( const Event& e ) {

	switch(e.keyboard.charCode) {

		case GLFW_KEY_DOWN:
			step(1);
			break;

		case GLFW_KEY_UP:
			step(-1);
			break;

		case GLFW_KEY_ENTER:
			select();
			break;
	}
}

void MainMenuController::axisChangeHandler(const Event& e) {

	if (e.joypad.axis != 1)
		return;

	char direction;

	if (abs(e.joypad.axisValue) < 0.2f)
		direction = 0;
	else
		direction = e.joypad.axisValue < 0 ? 1 : -1;
	
	if (direction != 0 && direction != m_iJoyDirection)
		step(direction);

	m_iJoyDirection = direction;
}

void MainMenuController::buttonDownHandler(const Event& e) {

	switch (e.joypad.button) {
	
		case 0: //Cross
			select();
			break;

		case 10:
			step(-1);
			break;

		case 12:
			step(1);
			break;
	}
}