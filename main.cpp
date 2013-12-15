#include "stdafx.h"

#include <iostream>
#include <random>
#include <ctime>

#include "Game.h"

int main(int argc, const char* argv[]){

	srand(time(nullptr));

	Game game;

	int result = game.init();
	if (result < 0)
		return result;

	game.loop();

	return 0;
}