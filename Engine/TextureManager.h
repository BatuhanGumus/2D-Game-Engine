#pragma once

#include <SDL.h>

class TextureManager
{
public:
	static SDL_Texture* LoadText(const char* fileName);
	static  void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

