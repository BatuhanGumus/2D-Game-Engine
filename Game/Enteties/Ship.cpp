#include "Ship.h"

Ship::Ship() : Component()
{
	rigidBody = nullptr;
    _maxHp = 0;
    _hp = 0;
    _laserSprite = nullptr;
}

Ship::~Ship()
= default;
