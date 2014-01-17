#include "stdafx.h"

#include <iostream>
#include <random>
#include <ctime>

#include "Game.h"
#include "Profiler.h"

int main(int argc, const char* argv[]){

	srand((unsigned int)time(nullptr));

	Game game;

	int result = game.init();
	if (result < 0)
		return result;

	game.loop();

	Profiler::instance()->logData();

	return 0;
}