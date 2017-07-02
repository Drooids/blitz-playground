#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int numFrames,
		int frameChangeSpeed) :
SDLGameObject(pParams)
{
	m_numFrames = numFrames;
	m_frameChangeSpeed = frameChangeSpeed;
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_frameChangeSpeed)) % m_numFrames));

	printf("%d\n", m_frameChangeSpeed, m_numFrames, m_currentFrame);

	// handleInput();

	SDLGameObject::update();
}

void AnimatedGraphic::handleInput()
{

}

void AnimatedGraphic::clean()
{
}
