#pragma once
#include "SDL_image.h"
#include <string>
#include <vector>

namespace ArtemisEngine
{
    class Sprite
    {
    public:
        Sprite(const char* textureSheet, int pixelH, int pixelW, std::string name);
        ~Sprite();

        SDL_Texture* Texture;
        int pixelH, pixelW;
        std::string name;

        static std::vector<Sprite*> sprites;

        static SDL_Texture* LoadText(const char* fileName);
        static void LoadSprite(const char* textureSheet, int pixelH, int pixelW, std::string name);
        static Sprite* GetSprite(std::string _name);
    };
}

