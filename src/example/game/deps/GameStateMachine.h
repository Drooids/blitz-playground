#ifndef GAMEMENUSTATE_H_DEFINED
#define GAMEMENUSTATE_H_DEFINED

#include "GameState.h"
#include <vector>
#include <iostream>

class GameStateMachine
{
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void update();
	void render();

private:
	std::vector<GameState* > m_gameStates;
};

#endif
