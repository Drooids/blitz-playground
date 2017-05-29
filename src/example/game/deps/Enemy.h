#ifndef ENEMY_H_DEFINED
#define ENEMY_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

using namespace std;

class Enemy : public SDLGameObject
{
public:

	Enemy(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();

	virtual void handleInput();

	virtual void clean();

};

#endif
