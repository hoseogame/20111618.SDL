#include "Game.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "HexaState.h"
#include "PauseState.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "GameStateMachine.h"
#include "StateParser.h"

#define DELAY_TIME 600
const std::string HexaState::s_hexaID = "HEXA";

void HexaState::update()
{
	if (m_HexaManager->GameOver()) 
	{
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
		return;
	}


	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	m_UIManager->setUIdata(m_HexaManager->GetUIdata());

	for (int i = 0; i < objectMaxCount; i++)
	{
		m_ManagerObjects[i]->update();
	}
}

void HexaState::render()
{
	for ( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->draw();
	}

	for (int i = 0; i < objectMaxCount; i++)
	{
		m_ManagerObjects[i]->render();
	}
}

bool HexaState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState( "test.xml", s_hexaID, &m_gameObjects, &m_textureIDList );

	m_HexaManager = new HexaManager();
	m_HexaManager->onEnter();
	m_UIManager = new UIManager();
	m_UIManager->onEnter();
	m_ManagerObjects.push_back(m_HexaManager);
	m_ManagerObjects.push_back(m_UIManager);

	objectMaxCount = m_ManagerObjects.size();

	return true;
}

bool HexaState::onExit()
{
	for ( int i = 0; i < m_gameObjects.size(); i++ )
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	m_textureIDList.clear();

	m_HexaManager->onExit();
	m_UIManager->onExit();

	delete m_HexaManager;
	delete m_UIManager;

	return true;
}

void HexaState::reset()
{
}