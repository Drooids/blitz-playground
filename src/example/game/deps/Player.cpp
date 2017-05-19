#include "Player.h"

using namespace std;

void Player::load(int x, int y, int width, int height, string textureID)
{
    GameObject::load(x, y, width, height, textureID);
}

void Player::draw(SDL_Renderer* pRenderer)
{
    GameObject::draw(pRenderer);
}

void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 200) % 6));
    m_x += 1;
}

void Player::clean()
{

}
