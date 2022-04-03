#pragma once

#include "Component.h"
#include "Sprite.h"


namespace ArtemisEngine
{
    class GameObject;

    class SpriteRenderer : public Component
    {
    public:
        explicit SpriteRenderer(Sprite* sprite);
        void Render() override;

    private:
        Sprite* sprite;
        SDL_Rect srcRect, destRect;
        void setDestRec();
    };
}

