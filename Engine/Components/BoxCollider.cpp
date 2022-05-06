#include <iostream>
#include "BoxCollider.h"
#include "Engine.h"
#include "SpriteRenderer.h"
#include "Color.h"
#include "Debug.h"

using namespace ArtemisEngine;

BoxCollider::BoxCollider(double width, double height) : Component()
{
	this->width = width;
	this->height = height;
    _initialized = true;
}

BoxCollider::BoxCollider(const Sprite* sprite) : Component()
{
	this->width = sprite->pixelW / Engine::pixelPerUnit;
	this->height = sprite->pixelH / Engine::pixelPerUnit;
    _initialized = true;
}

BoxCollider::BoxCollider()
{

}

void BoxCollider::Start()
{
    if(_initialized == true) return;

    SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();

    if (spriteRenderer != nullptr)
    {
        this->width = spriteRenderer->sprite->pixelW / Engine::pixelPerUnit;
        this->height = spriteRenderer->sprite->pixelH / Engine::pixelPerUnit;
        _initialized = true;
    }
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::Render()
{
    if (Debug::DrawColliders)
    {
        Color* red = new Color(255, 0, 0, 255);

        auto Xpos = transform->position->x;
        auto Ypos = transform->position->y;
        auto ToRight = width * transform->scale->x / 2;
        auto ToUp = height * transform->scale->y / 2;

        Vector2** points = new Vector2*[4];
        points[0] = new Vector2(Xpos + ToRight, Ypos + ToUp); // top right
        points[1] = new Vector2(Xpos + ToRight, Ypos - ToUp); // bottom right
        points[2] = new Vector2(Xpos - ToRight, Ypos - ToUp); // bottom left
        points[3] = new Vector2(Xpos - ToRight, Ypos + ToUp); // top left

        for (int i = 0; i < 4; ++i)
        {
            Debug::DrawLine(points[i], points[(i + 1) % 4], red);
        }
    }
}

