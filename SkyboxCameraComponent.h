#ifndef SKYBOXCAMERACOMPONENT_H
#define SKYBOXCAMERACOMPONENT_H

#include "Component.h"
#include "Event.h"

class SkyboxCameraComponent : public Component {

	public:
		SkyboxCameraComponent();

		void init(GameObject* refObj);
		void lateUpdate(const Event& e);

	private:
		GameObject* refObject;
};

#endif