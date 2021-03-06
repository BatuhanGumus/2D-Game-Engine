#include "FontManager.h"
#include "ArtemisEngine.h"
#include <iostream>

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

