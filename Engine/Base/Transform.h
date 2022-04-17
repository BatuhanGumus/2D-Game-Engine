#pragma once
#include "Vector2.h"
#include <memory>

namespace ArtemisEngine
{
    class Transform
    {
    public:
        Transform(Vector2* position, Vector2* scale);
        Transform();
        ~Transform();

        std::shared_ptr<Vector2> position, scale;
    private:

    };
}

