#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public:
	Player();
	virtual void load( const LoaderParams* pParams );
	virtual void draw();
	virtual void update();
	virtual void clean();
private :
	void handleInput();
};

class PlayCreator : public BaseCreator
{
public:
	GameObject* createGameObejct() const
	{
		return new Player();
	}
};
#endif // !_PLAYER_H_

