#include "ArtemisEngine.h"
#include <iostream>
#include "SDL_image.h"
#include "Input.h"

SDL_Renderer* ArtemisEngine::renderer = nullptr;

std::vector<MonoBehaviour*> ArtemisEngine::Monos;
std::vector<Text*> ArtemisEngine::textsToRender;

int ArtemisEngine::pixW;
int ArtemisEngine::pixH;
double ArtemisEngine::pixPerWorld;

ArtemisEngine::ArtemisEngine(const char* title, int xPos, int yPos, int widthPX, int heightPX, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialised!" << std::endl;

		int flags = 0;
		if (fullScreen == true)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(title, xPos, yPos, widthPX, heightPX, flags);

		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		if (TTF_Init() == -1)
		{
			std::cout << "Text Renderer Init Error" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	pixW = widthPX;
	pixH = heightPX;

	physicsEngine = new Physics();
}


ArtemisEngine::~ArtemisEngine()
{
}

void ArtemisEngine::HandleEvents()
{
	Input::ClearInputBuffer();

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			Input::PassInFrameInput(event.key);
			break;
		case SDL_KEYUP:
			Input::PassInFrameInput(event.key);
			break;
		default:
			break;
		}
	}

}

void ArtemisEngine::Update()
{
	for (int i = 0; i < Monos.size(); i++)
	{
		Monos[i]->Update();
	}
}

void ArtemisEngine::Render()
{
	SDL_RenderClear(renderer);

	for (int i = 0; i < Monos.size(); i++)
	{
		Monos[i]->Render();
	}

	for (int i = 0; i < textsToRender.size(); i++)
	{
		textsToRender[i]->Render();
	}

	SDL_RenderPresent(renderer);
}

void ArtemisEngine::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}

bool ArtemisEngine::IsGameRunning()
{
	return isRunning;
}
