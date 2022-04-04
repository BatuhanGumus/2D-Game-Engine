#include "BoxCollider.h"
#include "Engine.h"

using namespace ArtemisEngine;

BoxCollider::BoxCollider(double width, double height) : Component()
{
	this->width = width;
	this->height = height;
}

BoxCollider::BoxCollider(const Sprite* sprite)
{
	this->width = sprite->pixelW / Engine::pixPerWorld;
	this->height = sprite->pixelH / Engine::pixPerWorld;
}

BoxCollider::~BoxCollider()
{
}
