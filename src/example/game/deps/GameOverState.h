#ifndef GAMEOVERSTATE_H_DEFINED
#define GAMEOVERSTATE_H_DEFINED

#include <vector>

#include "Game.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "TextureManager.h"

#include "StateParser.h"
#include "MenuState.h"

class GameOverState : public MenuState
{
public:
	virtual void update();
	virtual void render();
	virtual void handleEvents();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }

private:
	static void s_gameOverToMain();
	static void s_restartPlay();

	static const std::string s_gameOverID;

	std::vector<GameObject*> m_gameObjects;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);
};

#endif
