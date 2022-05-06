#include <SDL.h>
#include "Engine.h"
#include "GameTime.h"
#include <iostream>
#include <memory>

using namespace ArtemisEngine;

int main(int args, char* argv[])
{
	std::srand(834793);

	const auto pixelW = 1200, pixelH = 900;
	const auto pixelPerWorldDist = 100.0;

	const auto FPS = 60;
	const auto frameDelay = 1000 / FPS;

    GameTime::fixedDeltaTime = 1.0 / FPS;

	Uint32 frameStart;
	int frameTime;

    std::unique_ptr<Engine> engine {new Engine("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                               pixelW, pixelH, pixelPerWorldDist, false)};

    std::unique_ptr<Physics> physicsEngine{new Physics()};
	
	engine->LoadAssets();
	engine->Awake();

	while (engine->IsGameRunning() == true)
	{
		frameStart = SDL_GetTicks();


		engine->HandleEvents();
		engine->Update();
		physicsEngine->Update();
		engine->Render();
        engine->UpdateGameObjectList();
        physicsEngine->UpdateBodyList();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	engine->Clean();

	return  0;
}
