#include  <iostream>
#include "Game.h"

#define FPS 60
#define UINT32 std::uint32_t

int main( int argc, char* args[] )
{
	const int DELAY_TIME = 1000.0f / FPS;
	UINT32  frameStart, frameTime;

	TheGame::Instance()->init( "SDL_Game_Create",
		100, 100, 1024, 768, false );

	while (TheGame::Instance()->running() )
	{
		frameStart = SDL_GetTicks();
		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		TheGame::Instance()->render();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}
	TheGame::Instance()->clean();
	return 0;
}