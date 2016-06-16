#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
enum BLOCKTYPE {
	NONE = 0,
	WALL = 9, 
	BLOCK1 = 1,
	BLOCK2 = 2,
	BLOCK3 = 3,
	BLOCK4 = 4,
	BLOCK5 = 5,
	BLOCK_COUNT = 6
};

class Block : public SDLGameObject
{
public:
	Block();

	virtual void draw();
	virtual void load( const LoaderParams* pParams );
	virtual void update();
	virtual void clean();

	void SetType(BLOCKTYPE _type)
	{
		m_Type = _type;
		if (_type == WALL) m_currentFrame = 0;
		else if (_type != NONE)
		{
			m_currentFrame = (int)_type;
		}
	}
	void SetType(int _type)
	{
		m_Type = (BLOCKTYPE)_type;
		if (_type == WALL) m_currentFrame = 0;
		else if (_type != NONE)
		{
			m_currentFrame = (int)_type;
		}
	}
	BLOCKTYPE GetType() { return m_Type; }
private:
	BLOCKTYPE m_Type;
};

class BlockCreator : public BaseCreator
{
	GameObject* createGameObject() const { return new Block(); }
};