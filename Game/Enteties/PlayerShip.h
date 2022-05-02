#pragma once
#include "Ship.h"

using namespace ArtemisEngine;

class PlayerShip : public Ship
{
public:
	PlayerShip();
	~PlayerShip();

    void Start() override;
	void Update() override;
	void Damage(int dmg) override;

private:
	
	Vector2 _acceleration;
	double _speed;
	Text* _playerHpText;
};