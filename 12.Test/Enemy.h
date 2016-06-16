#pragma once


#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
	Enemy();
	virtual void draw();
	virtual void load( const LoaderParams* pParams );
	virtual void update();
	virtual void clean();
};
