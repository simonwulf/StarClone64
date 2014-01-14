#include "MainMenuController.h"
#include "GOFactory.h"
#include "Scene.h"
#include "Input.h"
#include "Game.h"

MainMenuController::MainMenuController() {

	Input::instance()->registerEventHandler(Event::KEY_DOWN, this, &MainMenuController::keyDownhandler);
}

MainMenuController::~MainMenuController() {


}

void MainMenuController::setData( ModelRenderComponent* startItem, ModelRenderComponent* quitItem, Material* selected, Material* deselected ) {

	m_xStart = startItem;
	m_xQuit = quitItem;
	m_xMatSelected = selected;
	m_xMatDeselected = deselected;
}

void MainMenuController::keyDownhandler( const Event& e ) {

	switch(e.keyboard.charCode) {

		case GLFW_KEY_DOWN:
			index = (index + 1) % 2;
			break;

		case GLFW_KEY_UP:
			index = (index - 1) % 2;
			break;

		case GLFW_KEY_ENTER:
			switch(index) {
				case 0: Game::instance()->setState(Game::PLAY_STATE); break;
				case 1: Game::instance()->quit(); break;
			}
			break;
	}

	updateMenu();
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
