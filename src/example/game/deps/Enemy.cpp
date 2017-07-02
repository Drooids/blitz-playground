#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) :
SDLGameObject(pParams)
{
	m_velocity.setY(2);
	m_velocity.setX(0.001);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 200) % 6));

	if(m_position.getY() < 0)
	{
		m_velocity.setY(2);
	}
	else if(m_position.getY() > 400)
	{
		m_velocity.setY(-2);
	}

	// handleInput();

	SDLGameObject::update();
}

void Enemy::handleInput()
{
	Vector2D accX(0.1, 0);
	Vector2D accY(0, 0.1);

	if (TheInputHandler::Instance()->onKeyDown(SDL_SCANCODE_LEFT)) {
		m_acceleration = m_acceleration - accX;
	}
	if (TheInputHandler::Instance()->onKeyDown(SDL_SCANCODE_RIGHT)) {
		m_acceleration = m_acceleration + accX;
	}
	if (TheInputHandler::Instance()->onKeyDown(SDL_SCANCODE_UP)) {
		m_acceleration = m_acceleration - accY;
	}
	if (TheInputHandler::Instance()->onKeyDown(SDL_SCANCODE_DOWN)) {
		m_acceleration = m_acceleration + accY;
	}
}

void Enemy::clean()
{
}
