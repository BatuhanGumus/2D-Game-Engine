#pragma once
#include "Transform.h"
#include "Sprite.h"
#include "Component.h"

namespace ArtemisEngine
{
    class BoxCollider : public Component
    {
    public:
        BoxCollider(double width, double height);
        BoxCollider(const Sprite* sprite);
        ~BoxCollider();

        double width;
        double height;
    };

}

