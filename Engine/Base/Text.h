#pragma once
#include "SDL_ttf.h"
#include <string>
#include "Vector2.h"

namespace ArtemisEngine
{
    class Text
    {
    public:
        Text(std::string text, SDL_Color color, std::string fontName, int fontSize, Vector2 position);
        ~Text();

        void Render();

        std::string text;
        SDL_Color color;
        TTF_Font* font;
        int fontSize;
        Vector2 position;
    };
}

