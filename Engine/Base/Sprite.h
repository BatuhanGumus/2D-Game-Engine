#pragma once
#include "TextureManager.h"
#include <string>
#include <vector>

namespace ArtemisEngine
{
    class Sprite
    {
    public:
        Sprite(const char* textureSheet, int pixelH, int pixelW, std::string _name);
        ~Sprite();

        SDL_Texture* Texture;
        int pixelH, pixelW;
        std::string name;

        static std::vector<Sprite*> sprites;

        static void LoadSprite(const char* textureSheet, int pixelH, int pixelW, std::string _name);
        static Sprite* GetSprite(std::string _name);
    };
}

