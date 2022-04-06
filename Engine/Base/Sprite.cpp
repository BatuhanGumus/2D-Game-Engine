#include "Sprite.h"
#include <iostream>
#include "Engine.h"
#include "Debug.h"

using namespace ArtemisEngine;

Sprite::Sprite(const char* textureSheet, int pixelH, int pixelW, std::string _name)
{
	this->Texture = LoadText(textureSheet);
	this->pixelH = pixelH;
	this->pixelW = pixelW;
	this->name = _name;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(Texture);
}

std::vector<Sprite*> Sprite::sprites;

SDL_Texture* Sprite::LoadText(const char* fileName)
{
    SDL_Surface* tmpSurf = IMG_Load(fileName);
    if(tmpSurf == nullptr) Debug::Log("Texture Load Error: " + std::string (IMG_GetError()), Debug::Error);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);

    return tex;
}

void Sprite::LoadSprite(const char* textureSheet, int pixelH, int pixelW, std::string _name)
{
    Sprite* spriteAdd = new Sprite(textureSheet, pixelH, pixelW, _name);

    sprites.push_back(spriteAdd);
}

Sprite* Sprite::GetSprite(std::string _name)
{
    for (int i = 0; i < sprites.size(); i++)
    {
        if (sprites[i]->name == _name)
        {
            return sprites[i];
        }
    }

    Debug::Log("Sprite couldn't be found! (" + _name + ")", Debug::Warning);
    return nullptr;
}
