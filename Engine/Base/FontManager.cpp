#include "FontManager.h"
#include <iostream>
#include "Debug.h"

using namespace ArtemisEngine;

std::vector<Font> FontManager::fonts;

void FontManager::LoadFont(const char* fontName, const char* file, int fontSize)
{
	Font add;
	add.name = fontName;
	add.file = TTF_OpenFont(file, fontSize);

	if (add.file == NULL)
	{
        Debug::Log("Error lading font: " + std::string(fontName), Debug::Warning);
	}
	else
	{
		fonts.push_back(add);
	}
	
}

