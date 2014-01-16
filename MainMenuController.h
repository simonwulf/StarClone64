#ifndef MAINMENUCONTROLLER_H
#define MAINMENUCONTROLLER_H

#include "ControllerComponent.h"
#include "ModelRenderComponent.h"
#include "Material.h"
#include "Event.h"

class MainMenuController : public ControllerComponent {

	public:

		MainMenuController();
		~MainMenuController();

		void init(ModelRenderComponent* startItem, ModelRenderComponent* quitItem, Material* selected, Material* deselected);

	private:
		ModelRenderComponent* m_xStart;
		ModelRenderComponent* m_xQuit;
		Material* m_xMatSelected;
		Material* m_xMatDeselected;
		unsigned int index; //Hahaha Tommi, hur gillar du det här? Super quirk

		char m_iJoyDirection;

		void updateMenu();
		void step(int steps);
		void select();

		void keyDownHandler(const Event& e);
		void axisChangeHandler(const Event& e);
		void buttonDownHandler(const Event& e);
};

#endif // !MAINMENUCONTROLLER_H
