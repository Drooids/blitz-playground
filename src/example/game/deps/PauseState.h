#ifndef PAUSESTATE_H_DEFINED
#define PAUSESTATE_H_DEFINED

#include "Game.h"
#include "GameState.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "TextureManager.h"

class GameObject;

class PauseState : public GameState
{

public:
	// PlayState()
	~PauseState();

	virtual void update();
	virtual void render();
	virtual void handleEvents();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; };

private:
	static const std::string s_pauseID;

	static void s_pauseToMain();
	static void s_resumePlay();

	std::vector<GameObject*> m_gameObjects;
};

#endif
