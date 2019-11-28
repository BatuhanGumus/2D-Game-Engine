#pragma once
#include "SDL.h"

static class Input
{
public:
	static bool GetKeyDown(SDL_Keycode key);
	static bool GetKeyUp(SDL_Keycode key);
};

