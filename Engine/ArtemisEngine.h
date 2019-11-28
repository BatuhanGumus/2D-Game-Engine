#pragma once
#include "SDL.h"
#include "GameObject.h"
#include <vector>
#include "Physics.h"

class ArtemisEngine
{
public:
	ArtemisEngine(const char* title, int xPos, int yPos, int widthPX, int heightPX, bool fullScreen);
	~ArtemisEngine();

	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool IsGameRunning();

	void Awake();

	static SDL_Renderer* renderer;
	static SDL_Event event;

	static std::vector<GameObject*> spawnedObjects;

	static int pixW;
	static int pixH;
	static double pixPerWorld;

	Physics* physicsEngine;

private:
	bool isRunning;
	SDL_Window* window;
	
};

