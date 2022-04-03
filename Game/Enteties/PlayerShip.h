#pragma once
#include "Ship.h"

using namespace ArtemisEngine;

class PlayerShip : public Ship
{
public:
	PlayerShip(GameObject* holderObject);
	~PlayerShip();

	void Update() override;
	void Damage(int dmg) override;

private:
	
	Vector2 acc;
	double speed;
	Text* playerHpText;
};