#include "Game.h"
#include "InputHandler.h"
#include <Windows.h>
#include <sstream>

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler::InputHandler()
{
	m_mousePosition = new Vector2D(0, 0);
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

void InputHandler::clean()
{

}


bool InputHandler::AllKeyOff()
{
	if (KeyCount<=0)
	{
		return true;
	}
	return false;
}

void InputHandler::update()
{
	SDL_Event p_event;
	if (SDL_PollEvent(&p_event))
	{
		switch (p_event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->setRunning(false);
			TheGame::Instance()->clean();
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(p_event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(p_event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(p_event);
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		default:
			break;
		}
	}
}

void InputHandler::onKeyDown()
{
	m_keystates = SDL_GetKeyboardState(0);
}
void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(0);
}
void InputHandler::onMouseMove(SDL_Event& evt)
{
	if (evt.type == SDL_MOUSEMOTION)
	{
		m_mousePosition->setX(evt.motion.x);
		m_mousePosition->setY(evt.motion.y);
	}
}
void InputHandler::onMouseButtonDown(SDL_Event& evt)
{
	if (evt.type == SDL_MOUSEBUTTONDOWN)
	{
		if (evt.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseButtonStates[LEFT] = true;
		}
		if (evt.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseButtonStates[MIDDLE] = true;
		}
		if (evt.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseButtonStates[RIGHT] = true;
		}
	}
}
void InputHandler::onMouseButtonUp(SDL_Event& evt)
{
	if (evt.type == SDL_MOUSEBUTTONUP)
	{
		if (evt.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseButtonStates[LEFT] = false;
		}
		if (evt.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseButtonStates[MIDDLE] = false;
		}
		if (evt.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseButtonStates[RIGHT] = false;
		}
	}
}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else return false;
	}

	return false;
}
bool InputHandler::getMouseButtonState(int buttonNumber)
{
	return m_mouseButtonStates[buttonNumber];
}
Vector2D* InputHandler::getMousePosition()
{
	return m_mousePosition;
}
