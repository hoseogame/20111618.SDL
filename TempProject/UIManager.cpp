#include "UIManager.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"
#include "NumberObject.h"
#include "MenuButton.h"
#include <math.h>
#include "GameObject.h"

void UIManager::update()
{
	if (maxObjectCount == 0) return;

	m_stageNumber->setFrame(m_UIData.stage);
	for (int i = 0; i < 3; i++)
	{
		if (i != 0)
		{
			int temp = pow(10.0, i);
			m_comboNumber[i]->setFrame((m_UIData.maxcombo / temp));
			m_blockNumber[i]->setFrame((m_UIData.blockcount / temp));
		}
		else
		{
			m_comboNumber[i]->setFrame((m_UIData.maxcombo % 10));
			m_blockNumber[i]->setFrame((m_UIData.blockcount % 10));
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (i != 0)
		{
			int temp = pow(10.0, i);
			m_scoreNumber[i]->setFrame((m_UIData.score / temp)%temp);
		}
		else
		{
			m_scoreNumber[i]->setFrame((m_UIData.score % 10));
		}
	}
}

void UIManager::render()
{
	for (int i = 0; i < maxObjectCount; i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool UIManager::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/numbers.png",
		"numbers", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Block.png",
		"Block", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Count.png",
		"Count", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Stage.png",
		"Stage", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Score.png",
		"Score", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	Init();
	return true;
}

bool UIManager::onExit()
{

	for ( int i = m_gameObjects.size() - 1; i >= 0; i-- )
	{
		m_gameObjects[i]->clean();
		m_gameObjects.pop_back();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap( "numbers" );
	TheTextureManager::Instance()->clearFromTextureMap( "Block" );
	TheTextureManager::Instance()->clearFromTextureMap( "Count" );
	TheTextureManager::Instance()->clearFromTextureMap( "Stage" );
	TheTextureManager::Instance()->clearFromTextureMap( "Score" );
	return true;
}

void UIManager::Init()
{
	m_UIData.stage = 0;
	m_UIData.maxcombo = 0;
	m_UIData.blockcount = 0;
	m_UIData.score = 0;
	
	logo[0] = new MenuButton();
	logo[0]->load(new LoaderParams(
		375, 300, 200, 100, "Stage"));
	logo[1] = new MenuButton();
	logo[1]->load(new LoaderParams(
		375, 400, 200, 100, "Count"));
	logo[2] = new MenuButton();
	logo[2]->load(new LoaderParams(
		375, 500, 200, 100, "Block"));
	logo[3] = new MenuButton();
	logo[3]->load(new LoaderParams(
		375, 600, 200, 100, "Score"));
	m_gameObjects.push_back(logo[0]);
	m_gameObjects.push_back(logo[1]);
	m_gameObjects.push_back(logo[2]);
	m_gameObjects.push_back(logo[3]);


	m_stageNumber = new NumberObject();
	m_stageNumber->load(new LoaderParams(
		609, 340, 17, 31, "numbers"));

	m_gameObjects.push_back(m_stageNumber);

	for (int i = 0; i < 3; i++)
	{
		m_comboNumber[i] = new NumberObject();
		m_comboNumber[i]->load(new LoaderParams(660 - ((i + 1) * 17), 440, 17, 31, "numbers"));
		m_blockNumber[i] = new NumberObject();
		m_blockNumber[i]->load(new LoaderParams(660 - ((i + 1) * 17), 540, 17, 31, "numbers"));
		m_gameObjects.push_back(m_comboNumber[i]);
		m_gameObjects.push_back(m_blockNumber[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		m_scoreNumber[i] = new NumberObject();
		m_scoreNumber[i]->load(new LoaderParams(779 - ((i + 1) * 17), 640, 17, 31, "numbers"));
		m_gameObjects.push_back(m_scoreNumber[i]);
	}
	/*tempLP = new LoaderParams();

	logo[0] = new MenuButton();
	tempLP->setLoaderParams(375, 300, 200, 100, "Stage");
	logo[0]->load(tempLP);

	logo[1] = new MenuButton();
	tempLP->setLoaderParams(375, 400, 200, 100, "Count");
	logo[1]->load(tempLP);

	logo[2] = new MenuButton();
	tempLP->setLoaderParams(375, 500, 200, 100, "Block");
	logo[2]->load(tempLP);

	logo[3] = new MenuButton();
	tempLP->setLoaderParams(375, 600, 200, 100, "Score");
	logo[3]->load(tempLP);

	m_gameObjects.push_back( logo[0] );
	m_gameObjects.push_back( logo[1] );
	m_gameObjects.push_back( logo[2] );
	m_gameObjects.push_back( logo[3] );


	m_stageNumber = new NumberObject();
	tempLP->setLoaderParams(609, 340, 17, 31, "numbers");
	m_stageNumber->load(tempLP);

	m_gameObjects.push_back(m_stageNumber);

	for (int i = 0; i < 3; i++)
	{
		m_comboNumber[i] = new NumberObject();
		tempLP->setLoaderParams(660 - ((i + 1) * 17), 440, 17, 31, "numbers");
		m_comboNumber[i]->load(tempLP);
		m_blockNumber[i] = new NumberObject();
		tempLP->setLoaderParams(660 - ((i + 1) * 17), 540, 17, 31, "numbers");
		m_blockNumber[i]->load(tempLP);
		m_gameObjects.push_back(m_comboNumber[i]);
		m_gameObjects.push_back(m_blockNumber[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		m_scoreNumber[i] = new NumberObject();
		tempLP->setLoaderParams(779 - ((i + 1) * 17), 640, 17, 31, "numbers");
		m_scoreNumber[i]->load(tempLP);
		m_gameObjects.push_back(m_scoreNumber[i]);
	}
	delete tempLP;*/
	maxObjectCount = m_gameObjects.size();
}