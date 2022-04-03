#include "Transform.h"

using namespace ArtemisEngine;

Transform::Transform(Vector2* position, Vector2* scale)
{
	this->position = position;
	this->scale = scale;
}

Transform::~Transform()
{
	delete position;
	delete scale;
}

Transform::Transform()
{
    this->position = new Vector2();
    this->scale =  new Vector2();
}
