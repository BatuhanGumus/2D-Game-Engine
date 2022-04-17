#include "Transform.h"

using namespace ArtemisEngine;

Transform::Transform(Vector2* position, Vector2* scale)
{
	this->position = std::shared_ptr<Vector2>(position);
	this->scale = std::shared_ptr<Vector2>(scale);
}

Transform::~Transform()
{

}

Transform::Transform()
{
    this->position = std::shared_ptr<Vector2>(new Vector2());
    this->scale =  std::shared_ptr<Vector2>(new Vector2(1, 1));
}
