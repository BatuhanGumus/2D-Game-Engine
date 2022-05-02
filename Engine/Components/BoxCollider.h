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
        BoxCollider();
        virtual ~BoxCollider() override;

        virtual void Start() override;
        virtual void Render() override;

        double width;
        double height;
    private:
        bool _initialized;
    };

}

