#include "Block.h"
#include "TextureManager.h"
#include "Game.h"

Block::Block() :
	SDLGameObject()
{
	m_Type = WALL;
}

void Block::load( const LoaderParams* pParams )
{
	SDLGameObject::load( pParams );
}

void Block::draw()
{
	if (m_Type == NONE) return;

	TextureManager::Instance()->drawFrame(m_textureID,
		(Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame,
		TheGame::Instance()->get_Renderer(), SDL_FLIP_HORIZONTAL);
}

void Block::update()
{

}

void Block::clean()
{
	SDLGameObject::clean();
}