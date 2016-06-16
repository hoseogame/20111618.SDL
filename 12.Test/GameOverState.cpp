#include "Game.h"
#include "GameOverState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "MenuButton.h"

const std::string GameOverState::s_menuID = "GAMEOVER";

void GameOverState::update()
{
	for (int i = 0; i < objectMaxCount; i++)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < objectMaxCount; i++)
	{
		m_gameObjects[i]->draw();
	}
}
bool GameOverState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/gameover2.png",
		"gameover", TheGame::Instance()->get_Renderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main.png",
		"resumebutton", TheGame::Instance()->get_Renderer()))
	{
		return false;
	}

	
	GameObject* button2 = new MenuButton(s_exitFromMenu);
	button2->load( new LoaderParams( 412, 536,
		200, 80, "resumebutton" ) );
	GameObject* button1 = new MenuButton();
	button1->load( new LoaderParams( 312, 180,
		400, 100, "gameover" ) );
	m_gameObjects.push_back( button2 );
	m_gameObjects.push_back( button1 );

	objectMaxCount = m_gameObjects.size();
	std::cout << "entering MenuState\n";
	return true;
}
bool GameOverState::onExit()
{
	for (int i = m_gameObjects.size() - 1; i >= 0; i--)
	{
		m_gameObjects[i]->clean();
		m_gameObjects.pop_back();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
	return true;
}
void GameOverState::s_exitFromMenu()
{
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
	std::cout << "Exit button clicked\n";
}

void GameOverState::reset()
{
	m_gameObjects.resize(0);
}