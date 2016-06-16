#pragma once
#include "GameState.h"
#include "BaseManager.h"
#include "HexaManager.h"
#include "UIManager.h"

class HexaState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual void reset();
	virtual std::string getStateID() const { return s_hexaID; }
private:
	static const std::string s_hexaID;

	int objectMaxCount;
	std::vector<BaseManager*> m_ManagerObjects;
	std::vector<GameObject*> m_gameObjects;
	HexaManager* m_HexaManager;
	UIManager* m_UIManager;
};