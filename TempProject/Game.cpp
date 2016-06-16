#include <iostream>
#include "Game.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "NumberObject.h"
#include "Block.h"
#include "AnimatedGraphic.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}	
	
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if(m_pRenderer != 0)
			{
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	m_bRunning = true;

	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Block", new BlockCreator());
	TheGameObjectFactory::Instance()->registerType("NumberObject", new NumberObjectCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	TheInputHandler::Instance()->initialiseJoysticks();

	return true;
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}
}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	
	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	TheInputHandler::Instance()->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
