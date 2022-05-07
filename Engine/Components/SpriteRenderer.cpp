
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Engine.h"
#include <cmath>

using namespace ArtemisEngine;

SpriteRenderer::SpriteRenderer(Sprite *sprite) : Component()
{
    this->sprite = sprite;

    _srcRect.w = sprite->pixelW;
    _srcRect.h = sprite->pixelH;
    _srcRect.x = 0;
    _srcRect.y = 0;
}

void SpriteRenderer::Render()
{
    if (gameObject->type == Default)
    {
        setDestRec();
    }
    if (sprite != nullptr)
    {
        SDL_RenderCopy(Engine::renderer, sprite->Texture, &_srcRect, &_destRect);
    }
}

void SpriteRenderer::setDestRec()
{
    _destRect.w = std::floor(sprite->pixelW * transform->scale->x * Engine::pixW / 800.0);
    _destRect.h = std::floor(sprite->pixelH * transform->scale->y * Engine::pixH / 600.0);

    _destRect.x = std::floor( Vector2::CordToPixelX(gameObject->transform->position->x)
            - _srcRect.w * gameObject->transform->scale->x * (Engine::pixW / 800.0) / 2);

    _destRect.y = std::floor( Vector2::CordToPixelY(gameObject->transform->position->y)
            - _srcRect.h * gameObject->transform->scale->y * (Engine::pixH / 600.0) / 2);
}

SpriteRenderer::~SpriteRenderer()
= default;
