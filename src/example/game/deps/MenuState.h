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
	virtual void handleEvents();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; };

private:
	static const std::string s_menuID;

	// We have declared these functions as static; this is because our callback functionality
	// will only support static functions. It is a little more complicated to handle regular
	// member functions as function pointers, so we will avoid this and stick to static
	// functions
	static void s_menuToPlay();
	static void s_exitFromMenu();

	std::vector<GameObject*> m_gameObjects;
};

#endif
