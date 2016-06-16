#pragma once
#include <SDL.h>

class BaseManager
{
public:
	virtual void render() = 0;
	virtual void update() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
};