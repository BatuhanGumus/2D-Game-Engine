#include "FontManager.h"
#include <iostream>
#include "Debug.h"

using namespace ArtemisEngine;

std::vector<Font> FontManager::_fonts;

void FontManager::LoadFont(const char* fontName, const char* file, int fontSize)
{
	Font add;
	add.name = fontName;
	add.file = TTF_OpenFont(file, fontSize);

	if (add.file == nullptr)
	{
        Debug::Log("Error lading font: " + std::string(fontName), Debug::Warning);
	}
	else
	{
		_fonts.push_back(add);
	}
	
}

TTF_Font *FontManager::GetFont(const std::string& name)
{
    for (const auto &font : FontManager::_fonts)
    {
        if (name == font.name)
        {
            return font.file;
        }
    }

    return nullptr;
}

