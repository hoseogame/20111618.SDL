#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "Player.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}
bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/helicopter.png",
		"helicopter", TheGame::Instance()->get_Renderer()))
	{
		return false;
	}
	PlayCreator* factory = new PlayCreator();
	TheGameObjectFactory::Instance()->registerType("Player", factory);
	GameObject* player = TheGameObjectFactory::Instance()->create("Player");
	m_gameObjects.push_back(player);
	return true;
}
bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("helicopter");
	return true;
}

void PlayState::reset()
{
	m_gameObjects.resize(0);
}