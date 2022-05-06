#include "Sprite.h"
#include <iostream>
#include <utility>
#include "Engine.h"
#include "Debug.h"

using namespace ArtemisEngine;

Sprite::Sprite(const char* textureSheet, int pixelH, int pixelW, std::string name)
{
	this->Texture = LoadText(textureSheet);
	this->pixelH = pixelH;
	this->pixelW = pixelW;
	this->name = std::move(name);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(Texture);
}

std::vector<Sprite*> Sprite::sprites;

SDL_Texture* Sprite::LoadText(const char* fileName)
{
    auto tmpSurf = IMG_Load(fileName);
    if(tmpSurf == nullptr) Debug::Log("Texture Load Error: " + std::string (IMG_GetError()), Debug::Error);
    auto tex = SDL_CreateTextureFromSurface(Engine::renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);

    return tex;
}

void Sprite::LoadSprite(const char* textureSheet, int pixelH, int pixelW, std::string name)
{
    auto spriteAdd = new Sprite(textureSheet, pixelH, pixelW, std::move(name));

    sprites.push_back(spriteAdd);
}

Sprite* Sprite::GetSprite(const std::string& name)
{
    for (auto sprite : sprites)
    {
        if (sprite->name == name)
        {
            return sprite;
        }
    }

    Debug::Log("Sprite couldn't be found! (" + name + ")", Debug::Warning);
    return nullptr;
}
