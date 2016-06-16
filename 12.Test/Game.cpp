#include "Game.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

Game* Game::s_pInstance = nullptr;

Game::Game()
{
	m_pWindow = 0;
	m_pRenderer = 0;
	m_bRunning = false;
}

bool Game::init( const char* title, int xpos, int ypos, int width, int height, bool fullscreen )
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) >= 0 )
	{
		// 초기화 성공하면, window 생성
		m_pWindow = SDL_CreateWindow( title,
			xpos, ypos,
			width, height, fullscreen );

		// window 생성을 성공하면, renderer 생성 
		if ( m_pWindow != 0 ) {
			m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, 0 );
		}

		SDL_SetRenderDrawColor( m_pRenderer, 0, 0, 0, 255 );    // 색 (R,G,B,A) 지정 
	}
	else
	{
		return false; // sdl could not initialize
	}

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());

	m_bRunning = true;

	return true; // sdl initialize
}

void Game::render()
{
	SDL_RenderClear( m_pRenderer );  // 윈도우를 지정된 색으로 지움  
	m_pGameStateMachine->render();
	SDL_RenderPresent( m_pRenderer );   // 윈도우 보이기
}

void Game::clean()
{
	SDL_DestroyWindow( m_pWindow );
	SDL_DestroyRenderer( m_pRenderer );
	TheInputHandler::Instance()->clean();
	SDL_Quit();
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