#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

class Player : public SDLGameObject
{
public:

	Player(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	void handleInput();
};

#endif
