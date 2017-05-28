#include "Enemy.h"
// #include "SDL.h"

Enemy::Enemy(const LoaderParams* pParams) :
SDLGameObject(pParams)
{
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	// m_currentFrame = int(((SDL_GetTicks() / 200) % 6));

	m_position.setX(m_position.getX() + 0.5);
	m_position.setY(m_position.getY() + 0.5);
}

void Enemy::clean()
{
}
