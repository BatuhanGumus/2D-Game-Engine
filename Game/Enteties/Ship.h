#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/RigidBody.h"

class Ship : public GameObject
{
public:
	Ship(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale);
	~Ship();
	double speed;
private:
	
};
