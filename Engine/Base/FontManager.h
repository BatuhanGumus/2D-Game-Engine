#pragma once
#include "SDL_ttf.h"
#include <vector>
#include <string>

namespace ArtemisEngine
{
    struct Font
    {
        TTF_Font* file;
        std::string name;
    };

    class FontManager
    {
    public:
        static void LoadFont(const char* fontName, const char* file, int fontSize);
        static TTF_Font* GetFont(const std::string& name);

    private:
        static std::vector<Font> _fonts;
    };
}

