#pragma once

#include "GameState.h"

class GameObject;
class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual void reset();
	virtual std::string getStateID() const { return s_playID; }
private:
	static const std::string s_playID;

	std::vector<GameObject*> m_gameObjects;
};
