#include "TeapotSpin.h"

TeapotSpin::TeapotSpin() {
}

TeapotSpin::~TeapotSpin() {
}

void TeapotSpin::update(float delta, float deltaTime) {

	getGameObject()->appendRotation(glm::angleAxis(90.0f * delta, 0.0f, 0.0f, 1.0f));
}