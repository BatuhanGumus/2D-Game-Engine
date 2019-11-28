#include "SDL.h"
#include "ArtemisEngine.h"
#include "Input.h"
#include <iostream>
#include "Time.h"

void ConsoleInput()
{
	std::cout 
	<< std::endl 
	<< "============" << std::endl 
	<< "Game Paused!" << std::endl
	<< "============" << std::endl 
	<< std::endl;



	std::cout << ">";

	std::string Input;
	std::cin >> Input;
	std::cout << Input << std::endl;
}

int main(int args, char* argv[])
{
	const int pixelW = 1200, pixelH = 900;
	const double pixelPerWorldDist = 100.0;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Time::fixedDeltaTime = 1.0 / FPS;

	Uint32 frameStart;
	int frameTime;

	ArtemisEngine* engine = new ArtemisEngine("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pixelW, pixelH, false);
	ArtemisEngine::pixPerWorld = pixelPerWorldDist;
	engine->Awake();

	while (engine->IsGameRunning() == true)
	{
		if (Input::GetKeyDown(SDLK_BACKQUOTE))
		{
			ConsoleInput();
		}

		frameStart = SDL_GetTicks();

		engine->HandleEvents();
		engine->Update();
		engine->physicsEngine->Update();
		engine->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	engine->Clean();

	return  0;
}
