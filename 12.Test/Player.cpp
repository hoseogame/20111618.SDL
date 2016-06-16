#include <SDL.h>
#include "InputHandler.h"
#include "Player.h"

Player::Player() : SDLGameObject()
{
}

void Player::load( const LoaderParams* pParams )
{
	SDLGameObject::load( pParams );
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput();
	m_currentFrame = int((SDL_GetTicks() / 100) % 5);

	SDLGameObject::update();
}

void Player::handleInput()
{
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 50;
}

void Player::clean()
{
}