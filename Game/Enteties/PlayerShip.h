#pragma once
#include "Ship.h"

using namespace ArtemisEngine;

class PlayerShip : public Ship
{
public:
	PlayerShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale);
	~PlayerShip();

	void Update() override;
	void Damage(int dmg) override;

private:
	
	Vector2 acc;
	double speed;
	Text* playerHpText;
};