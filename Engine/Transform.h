#pragma once
#include "Vector2.h"

class Transform
{
public:
	Transform(Vector2* position, Vector2* scale);
	~Transform();

	Vector2 *position, *scale;
private:

};