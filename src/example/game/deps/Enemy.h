#ifndef ENEMY_H_DEFINED
#define ENEMY_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

class Enemy : public SDLGameObject
{
public:

	Enemy();

	virtual void load(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();

	virtual void handleInput();

	virtual void clean();

};

#endif
