#pragma once

#include <iostream>
#include <string>
#include <map>
#include "GameObject.h"

using namespace std;

class  BaseCreator
{
public:
	virtual GameObject* createGameObejct() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
	static GameObjectFactory* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new GameObjectFactory();
		}
		return s_pInstance;
	}

	bool registerType(string typeID, BaseCreator* pCreator);
	GameObject* create(string typeID);


protected:
private:

	map<string, BaseCreator*> m_creators;
	GameObjectFactory() {};
	~GameObjectFactory() {};

	static GameObjectFactory* s_pInstance;
}typedef TheGameObjectFactory;