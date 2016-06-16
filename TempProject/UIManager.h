#pragma once
#include "BaseManager.h"
#include "HexaManager.h"
#include "LoaderParams.h"
#include <vector>

class NumberObject;
class GameObject;

class UIManager : public BaseManager
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	void setUIdata(UIData _temp) { m_UIData = _temp; }
private:
	void Init();
private:
	UIData m_UIData;
	NumberObject* m_stageNumber;
	NumberObject* m_comboNumber[3];
	NumberObject* m_blockNumber[3];
	NumberObject* m_scoreNumber[10];
	GameObject* logo[4];

	int maxObjectCount;

	std::vector<GameObject*> m_gameObjects;
	std::vector<std::string> m_textureIDList;
};