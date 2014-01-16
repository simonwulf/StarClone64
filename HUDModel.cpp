#include "HUDModel.h"
#include <iostream>

HUDModel HUDModel::s_xInstance;

HUDModel::HUDModel() {

	m_iScore = 0;
	m_fHPFactor = 1.0f;
}

HUDModel* HUDModel::instance() {

	return &s_xInstance;
}

void HUDModel::reset() {

	m_iScore = 0;
	m_fHPFactor = 1.0f;
	sendUpdate();
}

void HUDModel::incrementScore() {

	setScore(m_iScore + 1);
}

void HUDModel::setScore(unsigned int score) {

	m_iScore = score;
	sendUpdate();
}

unsigned int HUDModel::getScore() {

	return m_iScore;
}

void HUDModel::setHPFactor(float factor) {

	m_fHPFactor = factor;
	sendUpdate();
}

float HUDModel::getHPFactor() {

	return m_fHPFactor;
}

void HUDModel::sendUpdate() {

	Event e(Event::HUD_UPDATE);

	dispatchEvent(e);
}