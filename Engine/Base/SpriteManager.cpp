#include "SpriteManager.h"
#include <iostream>

using namespace ArtemisEngine;

std::vector<Sprite*> SpriteManager::sprites;

void SpriteManager::LoadSprite(const char* textureSheet, int pixelH, int pixelW, std::string _name)
{
	Sprite* spriteAdd = new Sprite(textureSheet, pixelH, pixelW, _name);

	sprites.push_back(spriteAdd);
}

Sprite* SpriteManager::GetSprite(std::string _name)
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
