#pragma once
#include "Component.h"
#include "RigidBody.h"
#include "../GameManager.h"

using namespace ArtemisEngine;

class Ship : public Component
{
public:
	Ship();
	~Ship() override;
	virtual void Damage(int dmg) = 0;
    RigidBody* rigidBody;
protected:
	int _maxHp, _hp;
	Sprite* _laserSprite;
};
