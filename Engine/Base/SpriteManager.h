#pragma once

#include <vector>
#include "Sprite.h"

namespace ArtemisEngine
{
    class SpriteManager
    {
    public:

        static std::vector<Sprite*> sprites;

        static void LoadSprite(const char* textureSheet, int pixelH, int pixelW, std::string _name);
        static Sprite* GetSprite(std::string _name);

    };
}

