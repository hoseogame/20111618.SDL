#include <string>
#include <iostream>
#include "PauseState.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "LoaderParams.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "StateParser.h"
#include "InputHandler.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
} 

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);
	
	setCallbacks(m_callbacks);

	return true;
}

bool PauseState::onExit()
{
	for (int i = m_gameObjects.size() - 1; i >= 0; i--)
	{
		m_gameObjects[i]->clean();
		m_gameObjects.pop_back();
	}
	m_gameObjects.clear();
	m_gameObjects.resize(0);
	
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	m_textureIDList.clear();

	TheInputHandler::Instance()->reset();

	return true;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->popState();
	TheGame::Instance()->getGameStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getGameStateMachine()->popState();
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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