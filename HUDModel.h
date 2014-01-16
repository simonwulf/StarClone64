#ifndef HUDMODEL_H
#define HUDMODEL_H

#include "EventDispatcher.h"

//Model part of model-view-controller

class HUDModel : public EventDispatcher {

public:

	static HUDModel* instance();

	void reset();

	void incrementScore();
	void setScore(unsigned int score);
	unsigned int getScore();
	void setHPFactor(float factor);
	float getHPFactor();

private:

	HUDModel();

	static HUDModel s_xInstance;

	unsigned int m_iScore;
	float m_fHPFactor;

	void sendUpdate();
};

#endif