#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {

  public:

	enum {
	
		PLAY_STATE,

		STATE_N
	};

	GameState();
	~GameState();

  private:

	virtual void update() = 0;
};

#endif