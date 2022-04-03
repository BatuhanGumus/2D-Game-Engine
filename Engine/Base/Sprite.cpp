#include "Sprite.h"
#include <iostream>

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

std::vector<Sprite*> Sprite::sprites;

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

    std::cout << "Sprite couldn't be found! (" << _name << ")" << std::endl;
    return nullptr;
}
