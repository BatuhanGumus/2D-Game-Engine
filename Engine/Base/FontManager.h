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

        static std::vector<Font> fonts;

        static void LoadFont(const char* fontName, const char* file, int fontSize);

    private:

    };
}

