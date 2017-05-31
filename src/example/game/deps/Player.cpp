#include "Player.h"
#include "SDL.h"
#include <iostream>

Player::Player(const LoaderParams* pParams) :
SDLGameObject(pParams)
{

}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 200) % 6));

	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();

	SDLGameObject::update();
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->joysticksInitialised()) {

		// Controller 0

		/*
			Here, we first check whether xvalue of the left stick is more than 0 (that it has
			moved). If so, we set our Player x velocity to be the speed we want multiplied
			by xvalue of the left stick, and we know this is either 1 or -1. As you will know,
			multiplying a positive number by a negative number results in a negative number,
			so multiplying the speed we want by -1 will mean we are setting our x velocity to
			a minus value (move left). We do the same for the other stick and also the y values
		*/
		if (TheInputHandler::Instance()->xvalue(0, 1) > 0 || // joy = 0 stick = 1
			TheInputHandler::Instance()->xvalue(0, 1) < 0) {
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 1));
		}

		if (TheInputHandler::Instance()->yvalue(0, 1) > 0 || // joy = 0 stick = 1
			TheInputHandler::Instance()->yvalue(0, 1) < 0) {
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 1));
		}

		if (TheInputHandler::Instance()->xvalue(0, 2) > 0 || // joy = 0 stick = 2
			TheInputHandler::Instance()->xvalue(0, 2) < 0) {
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 2));
		}

		if (TheInputHandler::Instance()->yvalue(0, 2) > 0 || // joy = 0 stick = 2
			TheInputHandler::Instance()->yvalue(0, 2) < 0) {
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 2));
		}

		// Note: figure out which button it correspodents to
		// Yellow or Y on an Xbox controller
		if (TheInputHandler::Instance()->getButtonState(0, 3)) {
			m_velocity.setX(1);
		}

		// Controller 1, 2...
		// ...
	}

	if (TheInputHandler::Instance()->getMouseButtonState(
		TheInputHandler::Instance()->LEFT)) {
		// Vector2D acc(0.01, 0);
		// m_acceleration = m_acceleration + acc;
	}

	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 100;
}

void Player::clean()
{
}
