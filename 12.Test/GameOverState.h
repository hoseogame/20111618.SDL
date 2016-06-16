#pragma once

#include "GameState.h"

class GameObject;

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual void reset();
	virtual std::string getStateID() const { return s_menuID; }

private:
	static void s_exitFromMenu();
	static const std::string s_menuID;

	int objectMaxCount;
	std::vector<GameObject*> m_gameObjects;
};
