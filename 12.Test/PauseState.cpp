#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "MenuState.h"
#include "MenuButton.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	for (int i = 0; i < objectMaxCount; i++)
	{
		m_gameObjects[i]->update();
	}
}
void PauseState::render()
{
	for (int i = 0; i < objectMaxCount; i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/resume.png",
		"resumebutton", TheGame::Instance()->get_Renderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main.png",
		"mainbutton", TheGame::Instance()->get_Renderer()))
	{
		return false;
	}
	GameObject* button1 = new MenuButton(s_pauseToMain);
	button1->load( new LoaderParams( 412, 152, 200, 80, "mainbutton" ) );
	GameObject* button2 = new MenuButton(s_resumePlay);
	button2->load( new LoaderParams( 412, 536, 200, 80, "resumebutton" ) );
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	objectMaxCount = m_gameObjects.size();
	return true;
}
bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

	TheInputHandler::Instance()->clean();
	return true;
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}
void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->popState();
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::reset()
{
	m_gameObjects.resize(0);
}

