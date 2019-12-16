#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/RigidBody.h"
#include "../GameManager.h"

class Ship : public GameObject
{
public:
	Ship(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale);
	~Ship();
	virtual void Damage(int dmg) = 0;
protected:
	int maxhp, hp;
	Sprite* laserSprite;
};
