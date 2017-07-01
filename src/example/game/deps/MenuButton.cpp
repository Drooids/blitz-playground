#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams* pParams, void (*callback)()):
SDLGameObject(pParams), m_callback(callback)
{
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	//
	// If mouse position s larger than the starting point of the box
	// and smaller thend the end point of the box
	//
	// m_position.getX() -> +--------------------+ <- (m_position.getX() + m_width)
	//						+		 button		 +
	//						+--------------------+
	//						^
	//						|
	//			m_position.getY() + m_height
	//
	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		m_currentFrame = MOUSE_OVER;
		m_bReleased = true;

		if (TheInputHandler::Instance()->getMouseButtonState(
			TheInputHandler::Instance()->LEFT)) {

			m_currentFrame = CLICKED;

			m_callback();

			m_bReleased = false;
		}
	}
	else {
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}
