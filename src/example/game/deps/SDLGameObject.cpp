#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
GameObject(pParams), m_position(pParams->getX(), pParams->getY()),
m_acceleration(0, 0), m_velocity(0, 0)
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();

	m_currentFrame = 1;
	m_currentRow = 1;
}

void SDLGameObject::draw()
{
	/*
		Note:
			(int)m_position.getX(), (int)m_position.getY()
			Why do we have to cast them to int?
	*/
	TextureManager::Instance()->drawFrame(m_textureID,
		(int)m_position.getX(), (int)m_position.getY(),
		m_width, m_height,
		m_currentRow, m_currentFrame,
		TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{
	m_velocity = m_acceleration + m_velocity;
	m_position = m_position + m_velocity;

	// This doesn't get updated, why?
	// m_position += m_velocity;
	// m_position.print();
}

void SDLGameObject::clean()
{
}
