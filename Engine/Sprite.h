#pragma once
#include "TextureManager.h"

class Sprite
{
public:
	Sprite(const char* textureSheet, int pixelH, int pixelW);
	~Sprite();

	SDL_Texture* Texture;
	int pixelH, pixelW;
};
