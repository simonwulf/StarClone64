#include "TeapotSpin.h"
#include "Game.h"

TeapotSpin::TeapotSpin() {

	Game::instance()->registerEventHandler<TeapotSpin>(Event::GAME_UPDATE, this, &TeapotSpin::update);
}

TeapotSpin::~TeapotSpin() {

	Game::instance()->removeEventHandler<TeapotSpin>(Event::GAME_UPDATE, this, &TeapotSpin::update);
}

void TeapotSpin::update(const Event& e) {

	float delta = e.game.delta;

	getGameObject()->appendRotation(glm::angleAxis(90.0f * delta, 0.0f, 0.0f, 1.0f));
}