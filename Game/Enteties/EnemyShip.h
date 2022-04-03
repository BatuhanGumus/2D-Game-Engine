#pragma once
#include "Vector2.h"
#include "Text.h"
#include "Ship.h"

using namespace ArtemisEngine;

class EnemyShip : public Ship
{
public:
	EnemyShip(Vector2* pos);
	~EnemyShip();

	void Update() override;
	void Damage(int dmg) override;

	static int EnemyShipCount;
	
private:
	
	Vector2 distToText;
	double timeSinceShot;
	double randTime;
	void RandTimeForShot();
	Vector2 spawnedPos;

	Text* hpText;
};

