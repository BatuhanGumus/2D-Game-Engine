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
        virtual ~SpriteRenderer() override;
        void Render() override;

        Sprite* sprite;

    private:
        SDL_Rect _srcRect, _destRect;
        void setDestRec();
    };
}

