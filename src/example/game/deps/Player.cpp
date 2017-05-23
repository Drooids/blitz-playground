#include "Player.h"

Player::Player(const LoaderParams* pParams) :
SDLGameObject(pParams)
{

}

void Player::draw()
{
	SDLGameObject::draw();
	// GameObject::draw(pRenderer);
}

void Player::update()
{
	// m_currentFrame = int(((SDL_GetTicks() / 200) % 6));
	m_x += 1;
}

void Player::clean()
{
}
