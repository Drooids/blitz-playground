#ifndef PLAYSTATE_H_DEFINED
#define PLAYSTATE_H_DEFINED

#include "GameState.h"

class PlayState : public GameState
{

public:
	// PlayState()
	// ~PlayState()

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; };

private:
	static const std::string s_menuID;
};

#endif
