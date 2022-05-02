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
	this->width = sprite->pixelW / Engine::pixPerWorld;
	this->height = sprite->pixelH / Engine::pixPerWorld;
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
        this->width = spriteRenderer->sprite->pixelW / Engine::pixPerWorld;
        this->height = spriteRenderer->sprite->pixelH / Engine::pixPerWorld;
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

        double Xpos = transform->position->x;
        double Ypos = transform->position->y;
        double ToRight = width * transform->scale->x / 2;
        double ToUp = height * transform->scale->y / 2;

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

