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

	return true;
}

void UIManager::Init()
{
	m_UIData.stage = 0;
	m_UIData.maxcombo = 0;
	m_UIData.blockcount = 0;
	m_UIData.score = 0;
	
	LoaderParams* temp = new LoaderParams(
		609, 340, 17, 31, "numbers");
	m_stageNumber = new NumberObject();
	m_stageNumber->load(temp);
	delete temp;

	m_gameObjects.push_back(m_stageNumber);

	for (int i = 0; i < 3; i++)
	{
		LoaderParams* temp = new LoaderParams(660 - ((i + 1) * 17), 440, 17, 31, "numbers");
		LoaderParams* temp2 = new LoaderParams(660 - ((i + 1) * 17), 540, 17, 31, "numbers");
		m_comboNumber[i] = new NumberObject();
		m_comboNumber[i]->load(temp);
		m_blockNumber[i] = new NumberObject();
		m_blockNumber[i]->load(temp2);

		delete temp;
		delete temp2;

		m_gameObjects.push_back(m_comboNumber[i]);
		m_gameObjects.push_back(m_blockNumber[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		LoaderParams* temp = new LoaderParams(779 - ((i + 1) * 17), 640, 17, 31, "numbers");
		m_scoreNumber[i] = new NumberObject();
		m_scoreNumber[i]->load(temp);
		delete temp;
		m_gameObjects.push_back(m_scoreNumber[i]);
	}

	maxObjectCount = m_gameObjects.size();
}