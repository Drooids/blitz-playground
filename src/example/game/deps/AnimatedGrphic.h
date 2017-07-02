#ifndef ANIMATEDGRPHIC_H_DEFINED
#define ANIMATEDGRPHIC_H_DEFINED

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

class AnimatedGrphic : public SDLGameObject
{
public:

	AnimatedGrphic(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();

	virtual void handleInput();

	virtual void clean();
};

#endif
