#include "Sprite.h"

using namespace ArtemisEngine;

Sprite::Sprite(const char* textureSheet, int pixelH, int pixelW, std::string _name)
{
	this->Texture = TextureManager::LoadText(textureSheet);
	this->pixelH = pixelH;
	this->pixelW = pixelW;
	this->name = _name;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(Texture);
}