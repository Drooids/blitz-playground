#ifndef ENEMY_H_DEFINED
#define ENEMY_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"

using namespace std;

class Enemy : public SDLGameObject
{
public:

	Enemy(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

};

#endif
