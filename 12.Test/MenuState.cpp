#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "HexaState.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "Block.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	for (int i = 0; i < objectMaxCount; i++)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < objectMaxCount; i++)
	{
		m_gameObjects[i]->draw();
	}
}
bool MenuState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/button.png",
		"playbutton", TheGame::Instance()->get_Renderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/exit.png",
		"exitbutton", TheGame::Instance()->get_Renderer()))
	{
		return false;
	}
	
	GameObject* button1 = new MenuButton(s_menuToPlay);
	button1->load( new LoaderParams( 312, 180, 400, 100, "playbutton" ) );
	GameObject* button2 = new MenuButton(s_exitFromMenu);
	button2->load( new LoaderParams( 312, 480, 400, 100, "exitbutton" ) );

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	objectMaxCount = m_gameObjects.size();

	return true;
}
bool MenuState::onExit()
{
	TheTextureManager::Instance()->clearFromTextureMap( "playbutton" );
	TheTextureManager::Instance()->clearFromTextureMap( "exitbutton" );

	for (int i = m_gameObjects.size()-1 ; i >= 0; i--)
	{
		m_gameObjects[i]->clean();
		m_gameObjects.pop_back();
	}
	m_gameObjects.clear();
	
	return true;
}

void MenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new HexaState());
}

void MenuState::s_exitFromMenu()
{
	TheGame::Instance()->setRunning(false);
}

void MenuState::reset()
{
	m_gameObjects.resize(0);
}