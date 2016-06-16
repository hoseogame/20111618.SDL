#pragma once
#include "SDLGameObject.h"

enum  Button_State
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};

class MenuButton : public SDLGameObject
{
public:
	MenuButton();
	MenuButton( void ( *callback )() );

	bool m_bReleased;

	virtual void draw();
	virtual void load( const LoaderParams* pParams );
	virtual void update();
	virtual void clean();
private:
	void (*m_callback)();
};