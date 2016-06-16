#include "NumberObject.h"

NumberObject::NumberObject() :
	SDLGameObject()
{
}

void NumberObject::load( const LoaderParams* pParams )
{
	SDLGameObject::load( pParams );
}

void NumberObject::draw()
{
	SDLGameObject::draw();
}

void NumberObject::update()
{
}

void NumberObject::clean()
{
	SDLGameObject::clean();
}