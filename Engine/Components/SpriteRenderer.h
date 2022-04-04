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

        Sprite* sprite;

    private:
        SDL_Rect srcRect, destRect;
        void setDestRec();
    };
}

