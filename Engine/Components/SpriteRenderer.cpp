
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Engine.h"

using namespace ArtemisEngine;

SpriteRenderer::SpriteRenderer(Sprite *sprite) : Component()
{
    this->sprite = sprite;

    srcRect.w = sprite->pixelW;
    srcRect.h = sprite->pixelH;
    srcRect.x = 0;
    srcRect.y = 0;
}

void SpriteRenderer::Render()
{
    if (gameObject->type == Default)
    {
        setDestRec();
    }
    if (sprite != nullptr)
    {
        TextureManager::Draw(sprite->Texture, srcRect, destRect);
    }
}

void SpriteRenderer::setDestRec()
{
    destRect.w = sprite->pixelW * transform->scale->x * Engine::pixW / 800.0;
    destRect.h = sprite->pixelH * transform->scale->y * Engine::pixH / 600.0;
    destRect.x = Vector2::cordToPixelX(gameObject->transform->position->x) - srcRect.w * gameObject->transform->scale->x * (Engine::pixW / 800.0) / 2;
    destRect.y = Vector2::cordToPixelY(gameObject->transform->position->y) - srcRect.h * gameObject->transform->scale->y * (Engine::pixH / 600.0) / 2;
}