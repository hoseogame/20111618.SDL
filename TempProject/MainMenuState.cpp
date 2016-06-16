#include <string>
#include <iostream>
#include "MainMenuState.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "HexaState.h"
#include "LoaderParams.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MainMenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MainMenuState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	setCallbacks(m_callbacks);

	return true;
}

bool MainMenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	m_textureIDList.clear();

	TheInputHandler::Instance()->reset();
	return true;
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new PlayState());
	//TheGame::Instance()->getGameStateMachine()->changeState(new HexaState());
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*> (m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}