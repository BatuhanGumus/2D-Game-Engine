#include "FontManager.h"
#include "Engine.h"
#include <iostream>

using namespace ArtemisEngine;

std::vector<Font> FontManager::fonts;

void FontManager::LoadFont(const char* fontName, const char* file, int fontSize)
{
	Font add;
	add.name = fontName;
	add.file = TTF_OpenFont(file, fontSize);

	if (add.file == NULL)
	{
		std::cout << "Error lading font: " << fontName << std::endl;
	}
	else
	{
		fonts.push_back(add);
	}
	
}

