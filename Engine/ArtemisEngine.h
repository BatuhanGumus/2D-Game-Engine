#pragma once
#include "SDL.h"
#include "GameObject.h"
#include <vector>
#include "Physics.h"
#include "Text.h"

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
	void LoadAssets();

	static SDL_Renderer* renderer;
	SDL_Event event;

	static std::vector<GameObject*> spawnedObjects;
	static std::vector<Text*> textsToRender;

	static int pixW;
	static int pixH;
	static double pixPerWorld;

	Physics* physicsEngine;

private:
	bool isRunning;
	SDL_Window* window;
	
};

