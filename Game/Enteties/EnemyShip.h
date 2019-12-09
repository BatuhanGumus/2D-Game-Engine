#pragma once
#include "../../Engine/Vector2.h"
#include "../../Engine/SpriteManager.h"
#include "Ship.h"
#include "../GameManager.h"

class EnemyShip : public Ship
{
public:
	EnemyShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale);
	~EnemyShip();

	void Update() override;
	void Damage(int dmg);

	static int EnemyShipCount;
	GameManager* GM;
private:
	
	Vector2 distToText;
	Sprite* laserSprite;
	double timeSinceShot;
	double randTime;
	void RandTimeForShot();
};

