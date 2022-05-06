#include "Engine.h"
#include <iostream>
#include "SDL_image.h"
#include "Input.h"
#include <algorithm>
#include "Debug.h"

using namespace ArtemisEngine;

SDL_Renderer* Engine::renderer = nullptr;
std::vector<GameObject*> Engine::_gameObjects;
std::queue<GameObject*> Engine::_gameObjectsToAdd;
std::queue<GameObject*> Engine::_gameObjectsToRemove;
std::vector<Text*> Engine::textsToRender;

int Engine::pixW;
int Engine::pixH;
double Engine::pixelPerUnit;

Engine::Engine(const char* title, int xPos, int yPos, int widthPX, int heightPX, int pixelPerUnit, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
        Debug::Log("Subsystem Initialised!");

		int flags = 0;
		if (fullScreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		_window = SDL_CreateWindow(title, xPos, yPos, widthPX, heightPX, flags);

		if (_window)
		{
            Debug::Log("Window created!");
		}

		renderer = SDL_CreateRenderer(_window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            Debug::Log("Renderer created!");
		}

		if (TTF_Init() == -1)
		{
            Debug::Log("Text Renderer Init Error: " + std::string( SDL_GetError()), Debug::Warning);
		}

		_isRunning = true;
	}
	else
	{
		_isRunning = false;
	}

	pixW = widthPX;
	pixH = heightPX;
    this->pixelPerUnit = pixelPerUnit;
}


Engine::~Engine()
{
}

void Engine::HandleEvents()
{
	Input::ClearInputBuffer();

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_isRunning = false;
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


void Engine::Update()
{
    for(auto gameObject : _gameObjects)
    {
        gameObject->UpdateComponents();
    }
}

void Engine::Render()
{
	SDL_RenderClear(renderer);

    for(auto gameObject : _gameObjects)
    {
        gameObject->RenderComponents();
    }

	for (auto text : textsToRender)
	{
        text->Render();
	}

	SDL_RenderPresent(renderer);
}

void Engine::Clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
    Debug::Log("Game cleaned!");
}

bool Engine::IsGameRunning() const
{
	return _isRunning;
}

void Engine::GameObjectCreated(GameObject *gameObject)
{
    _gameObjectsToAdd.push(gameObject);
}

void Engine::UpdateGameObjectList()
{
    while(!_gameObjectsToRemove.empty())
    {
        auto found = std::find(_gameObjects.begin(), _gameObjects.end(), _gameObjectsToRemove.front());
        if (found != _gameObjects.end())
        {
            _gameObjects.erase(found);
        }

        auto rb = _gameObjectsToRemove.front()->GetComponent<RigidBody>();
        if (rb != nullptr)
        {
            Physics::RigidBodyDeleted(rb);
        }

        delete _gameObjectsToRemove.front();
        _gameObjectsToRemove.pop();
    }

    while(!_gameObjectsToAdd.empty())
    {
        _gameObjects.push_back(_gameObjectsToAdd.front());
        _gameObjectsToAdd.pop();
    }
}

void Engine::Destroy(GameObject *gameObject)
{
    _gameObjectsToRemove.push(gameObject);
}
