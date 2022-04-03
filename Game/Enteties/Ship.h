#pragma once
#include "GameObject.h"
#include "RigidBody.h"
#include "../GameManager.h"

using namespace ArtemisEngine;

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
