#include "Player.h"

Player::Player(const LoaderParams* pParams) :
SDLGameObject(pParams)
{

}

/*
void Player::load(int x, int y, int width, int height, string textureID)
{
    GameObject::load(x, y, width, height, textureID);
}
*/

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
