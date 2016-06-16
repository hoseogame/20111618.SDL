#pragma once
#include "SDLGameObject.h"

class NumberObject : public SDLGameObject
{
public:
	NumberObject();

	virtual void draw();
	virtual void load( const LoaderParams* pParams );
	virtual void update();
	virtual void clean();

	void setFrame(int framenumber) { m_currentFrame = framenumber; }
private:
};

