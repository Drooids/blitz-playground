#ifndef ENEMY_H_DEFINED
#define ENEMY_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "BaseCreator.h"

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

class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Enemy();
	}
};

#endif
