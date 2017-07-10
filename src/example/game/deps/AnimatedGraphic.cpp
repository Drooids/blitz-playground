#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams) :
SDLGameObject()
{
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
	m_currentFrame = 1; // int(((SDL_GetTicks() / (1000 / m_frameChangeSpeed)) % m_numFrames));

	//printf("%d\n", m_frameChangeSpeed, m_numFrames, m_currentFrame);

	// handleInput();

	SDLGameObject::update();
}

void AnimatedGraphic::handleInput()
{

}

void AnimatedGraphic::clean()
{
}
