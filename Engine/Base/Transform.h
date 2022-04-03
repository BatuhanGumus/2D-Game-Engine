#pragma once
#include "Vector2.h"

namespace ArtemisEngine
{
    class Transform
    {
    public:
        Transform(Vector2* position, Vector2* scale);
        Transform();
        ~Transform();

        Vector2 *position, *scale;
    private:

    };
}

