#pragma once
#include "GameState.h"

class GameObject;

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual void reset();
	virtual std::string getStateID() const { return s_pauseID; }
private:
	static const std::string s_pauseID;
	static void s_resumePlay();
	static void s_pauseToMain();

	int objectMaxCount;

	std::vector<GameObject*> m_gameObjects;
};