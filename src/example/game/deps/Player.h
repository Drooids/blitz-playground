#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

#include "BaseCreator.h"

class Player : public SDLGameObject
{
public:

	Player();

	virtual void load(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	void handleInput();
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};

#endif
