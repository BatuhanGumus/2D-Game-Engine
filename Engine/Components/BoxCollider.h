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
        explicit BoxCollider(const Sprite* sprite);
        BoxCollider();
        ~BoxCollider() override;

        void Start() override;
        void Render() override;

        double width;
        double height;
    private:
        bool _initialized;
    };

}

