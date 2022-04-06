#pragma once

#include "SDL.h"

class Color
{
public:
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Color(float r, float g, float b, float a);
};
