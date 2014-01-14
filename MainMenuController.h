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

		void setData(ModelRenderComponent* startItem, ModelRenderComponent* quitItem, Material* selected, Material* deselected);
		void keyDownhandler(const Event& e);

	private:
		ModelRenderComponent* m_xStart;
		ModelRenderComponent* m_xQuit;
		Material* m_xMatSelected;
		Material* m_xMatDeselected;
		unsigned int index; //Hahaha Tommy, hur gillar du det här? Super quirk

		void updateMenu();
};

#endif // !MAINMENUCONTROLLER_H
