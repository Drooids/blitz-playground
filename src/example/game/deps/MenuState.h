#ifndef MENUSTATE_H_DEFINED
#define MENUSTATE_H_DEFINED

#include <vector>

#include "Game.h"
#include "GameState.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "TextureManager.h"

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

	std::vector<GameObject*> m_gameObjects;
};

#endif