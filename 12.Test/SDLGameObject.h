#pragma once

#include <string>
#include "GameObject.h"
#include "Vector2D.h"

class LoaderParams;

class SDLGameObject : public GameObject
{
public :
	SDLGameObject();
	virtual void load( const LoaderParams* pParams );
	virtual void draw();
	virtual void update();
	virtual void clean();

	void setFrame(int number)
	{
		m_currentFrame = number;
	}

protected:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	int m_width, m_height;
	int m_currentRow, m_currentFrame;
	int m_numFrames;
	std::string m_textureID;
};