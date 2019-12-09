#pragma once
#include "TextureManager.h"
#include <string>

class Sprite
{
public:
	Sprite(const char* textureSheet, int pixelH, int pixelW, std::string _name);
	~Sprite();

	SDL_Texture* Texture;
	int pixelH, pixelW;
	std::string name;
};
