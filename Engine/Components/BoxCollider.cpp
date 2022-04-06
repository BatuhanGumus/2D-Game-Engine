#include "BoxCollider.h"
#include "Engine.h"
#include "SpriteRenderer.h"

using namespace ArtemisEngine;

BoxCollider::BoxCollider(double width, double height) : Component()
{
	this->width = width;
	this->height = height;
    initialized = true;
}

BoxCollider::BoxCollider(const Sprite* sprite) : Component()
{
	this->width = sprite->pixelW / Engine::pixPerWorld;
	this->height = sprite->pixelH / Engine::pixPerWorld;
    initialized = true;
}

BoxCollider::BoxCollider()
{

}

void BoxCollider::Start()
{
    if(initialized == true) return;

    SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();

    if (spriteRenderer != nullptr)
    {
        this->width = spriteRenderer->sprite->pixelW / Engine::pixPerWorld;
        this->height = spriteRenderer->sprite->pixelH / Engine::pixPerWorld;
        initialized = true;
    }
}


BoxCollider::~BoxCollider()
{
}

