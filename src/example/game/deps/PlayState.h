#ifndef PLAYSTATE_H_DEFINED
#define PLAYSTATE_H_DEFINED

#include "Game.h"
#include "GameState.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "TextureManager.h"

class PlayState : public GameState
{

public:
	// PlayState()
	// ~PlayState()

	virtual void update();
	virtual void render();
	virtual void handleEvents();

	virtual bool onEnter();
	virtual bool onExit();

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	virtual std::string getStateID() const { return s_playID; };

private:
	static const std::string s_playID;

	std::vector<GameObject*> m_gameObjects;
};

#endif
