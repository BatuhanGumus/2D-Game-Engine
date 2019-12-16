#include "SDL.h"
#include "ArtemisEngine.h"
#include "Time.h"
#include <ctime>
#include <cstdlib>

int main(int args, char* argv[])
{
	std::srand(std::time(NULL));

	const int pixelW = 1200, pixelH = 900;
	const double pixelPerWorldDist = 100.0;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Time::fixedDeltaTime = 1.0 / FPS;

	Uint32 frameStart;
	int frameTime;

	ArtemisEngine* engine = new ArtemisEngine("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pixelW, pixelH, false);
	ArtemisEngine::pixPerWorld = pixelPerWorldDist;
	
	engine->LoadAssets();
	engine->Awake();

	while (engine->IsGameRunning() == true)
	{
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
