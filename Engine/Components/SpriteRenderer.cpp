
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Engine.h"

using namespace ArtemisEngine;

SpriteRenderer::SpriteRenderer(GameObject* holderObject, Sprite *sprite) : Component(holderObject)
{
    this->sprite = sprite;

    srcRect.w = sprite->pixelW;
    srcRect.h = sprite->pixelH;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.w = sprite->pixelW * holderObject->transform->scale->x * Engine::pixW / 800.0;
    destRect.h = sprite->pixelH * holderObject->transform->scale->y * Engine::pixH / 600.0;
}

void SpriteRenderer::Render()
{
    if (holderObject->type == Default)
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
    destRect.x = Vector2::cordToPixelX(holderObject->transform->position->x) - srcRect.w * holderObject->transform->scale->x * (Engine::pixW / 800.0) / 2;
    destRect.y = Vector2::cordToPixelY(holderObject->transform->position->y) - srcRect.h * holderObject->transform->scale->y * (Engine::pixH / 600.0) / 2;
}