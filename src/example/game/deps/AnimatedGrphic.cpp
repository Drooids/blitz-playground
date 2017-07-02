#include "AnimatedGrphic.h"

AnimatedGrphic::AnimatedGrphic(const LoaderParams* pParams) :
SDLGameObject(pParams)
{
}

void AnimatedGrphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGrphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_frameChangeSpeed)) % m_numFrames));

	// handleInput();

	SDLGameObject::update();
}

void AnimatedGrphic::handleInput()
{

}

void AnimatedGrphic::clean()
{
}
