#ifndef MENUSTATE_H_DEFINED
#define MENUSTATE_H_DEFINED

#include "GameState.h"

class MenuState : public GameState
{
public:
	// MenuState()
	// ~MenuState()

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; };

private:
	static const std::string s_menuID;
};

#endif