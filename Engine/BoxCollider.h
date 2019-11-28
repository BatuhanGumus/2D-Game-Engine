#pragma once
#include "Transform.h"
#include "Sprite.h"

class BoxCollider
{
public:
	BoxCollider(double width, double height);
	BoxCollider(const Sprite* sprite);
	~BoxCollider();

	double width;
	double height;
};
