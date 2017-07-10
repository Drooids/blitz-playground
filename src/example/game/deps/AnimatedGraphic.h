#ifndef ANIMATEDGRAPHIC_H_DEFINED
#define ANIMATEDGRAPHIC_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

class AnimatedGraphic : public SDLGameObject
{
public:

	AnimatedGraphic(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();

	virtual void handleInput();

	virtual void clean();
};

#endif
