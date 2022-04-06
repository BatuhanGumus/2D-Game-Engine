#include "Color.h"

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(float r, float g, float b, float a)
{
    this->r = (Uint8)(r * 255);
    this->g = (Uint8)(r * 255);
    this->b = (Uint8)(r * 255);
    this->a = (Uint8)(r * 255);
}
