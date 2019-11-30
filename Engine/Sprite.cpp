#include "Sprite.h"


Sprite::Sprite(const char* textureSheet, int pixelH, int pixelW)
{
	this->Texture = TextureManager::LoadText(textureSheet);
	this->pixelH = pixelH;
	this->pixelW = pixelW;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(Texture);
}