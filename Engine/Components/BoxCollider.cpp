#include "BoxCollider.h"
#include "ArtemisEngine.h"

BoxCollider::BoxCollider(double width, double height)
{
	this->width = width;
	this->height = height;
}

BoxCollider::BoxCollider(const Sprite* sprite)
{
	this->width = sprite->pixelW / ArtemisEngine::pixPerWorld;
	this->height = sprite->pixelH / ArtemisEngine::pixPerWorld;
}

BoxCollider::~BoxCollider()
{
}
