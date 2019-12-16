#pragma once
#include "../../Engine/Vector2.h"
#include "../../Engine/Text.h"
#include "Ship.h"

class EnemyShip : public Ship
{
public:
	EnemyShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale);
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

