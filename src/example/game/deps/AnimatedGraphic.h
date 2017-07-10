#ifndef ANIMATEDGRAPHIC_H_DEFINED
#define ANIMATEDGRAPHIC_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "BaseCreator.h"

class AnimatedGraphic : public SDLGameObject
{
public:

	AnimatedGraphic();

	virtual void load(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();

	virtual void handleInput();

	virtual void clean();
};

class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic();
	}
};

#endif
