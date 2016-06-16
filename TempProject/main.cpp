#include <Windows.h>
#include <iostream>
#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
	const int DELAY_TIME = 1000.0f / FPS;
	UINT32  frameStart, frameTime;

	TheGame::Instance()->init("SDL_Game_Create",
		100, 100, 1024, 768, false);

	while (TheGame::Instance()->running())
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

/*
Uint32 frameStart, frameTime;

// This code enables the console while running the program, to see the couts output

AllocConsole();
freopen("CON", "w", stdout);

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! Remove before release !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!


std::cout <<"game init attemp... \n";
if(TheGame::Instance()->init("Chapter 1", 100, 100, 640, 480, false))
{
std::cout << "game init success!\n";
while(TheGame::Instance()->running())
{
frameStart = SDL_GetTicks();

TheGame::Instance()->handleEvents();
TheGame::Instance()->update();
TheGame::Instance()->render();

frameTime = SDL_GetTicks() - frameStart;

if (frameTime < DELAY_TIME)
{
SDL_Delay(DELAY_TIME-frameTime);
}
}
}
else
{
std::cout << "game init failure - " << SDL_GetError() << "\n";
return -1;
}

std::cout << "game closing... \n";
TheGame::Instance()->clean();

return 0;
*/