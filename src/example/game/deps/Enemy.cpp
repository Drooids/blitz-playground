#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) :
SDLGameObject(pParams)
{

}

/*
void Enemy::load(int x, int y, int width, int height, string textureID)
{
	GameObject::load(x, y, width, height, textureID);
}
*/

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_y += 1;
	m_x += 1;

	// m_currentFrame = int(((SDL_GetTicks() / 200) % 6));
}

void Enemy::clean()
{
}
