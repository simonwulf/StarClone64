#include "FMODTest.h"
#include "Game.h"
#include "AudioManager.h"

unsigned int testSound = 0;
FMODTest::FMODTest() : Component(CUSTOM) {

	Log::Writeln("FMODTest Component ~", Log::COLOR_LIGHT_PURPLE);
	Game::instance()->registerEventHandler<FMODTest>(Event::KEY_DOWN, this, &FMODTest::keyDownHandler);
	testSound = AudioManager::instance()->loadAudio("ball.wav");
}

FMODTest::~FMODTest() {

	Game::instance()->removeEventHandler<FMODTest>(Event::KEY_DOWN, this, &FMODTest::keyDownHandler);
}

void FMODTest::keyDownHandler( const Event& e ) {

	switch (e.keyboard.charCode)
	{
		case GLFW_KEY_SPACE:
		{
			AudioManager::instance()->playAudio(testSound, this->getGameObject());
			break;
		}
	}
}
