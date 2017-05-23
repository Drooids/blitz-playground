#include "Enemy.h"

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

	m_y += 1;
	m_x += 1;
}

void Enemy::clean()
{
}
