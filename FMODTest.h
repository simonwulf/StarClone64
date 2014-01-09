#ifndef FMODTEST_H
#define FMODTEST_H

#include "Component.h"
#include "Event.h"

class FMODTest : public Component {

	public:

		FMODTest();
		~FMODTest();

	void keyDownHandler(const Event& e);
};

#endif