#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

class LoaderParams;

class GameObject
{
public:

	virtual void draw( ) = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void load( const LoaderParams* pParams ) = 0;
protected:
	GameObject() {}
	//GameObject( const LoaderParams* pParams ) {}
	virtual ~GameObject() {}
};
#endif // !_GAMEOBJECT_H_

