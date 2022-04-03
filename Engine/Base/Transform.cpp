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
