#include "InputHandler.h"
#include "MenuButton.h"

MenuButton::MenuButton() :
	SDLGameObject()
{
	m_currentFrame = MOUSE_OUT;
}

MenuButton::MenuButton(void (*callback)()) :
	SDLGameObject(), m_callback(callback)
{
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::load( const LoaderParams* pParams )
{
	SDLGameObject::load( pParams );
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width) &&
		pMousePos->getX() > m_position.getX() &&
		pMousePos->getY() < (m_position.getY() + m_height) &&
		pMousePos->getY() > m_position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_bReleased = false;
			m_callback(); // 시발 터지지마
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else m_currentFrame = MOUSE_OUT;
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}