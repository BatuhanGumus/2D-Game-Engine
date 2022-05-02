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

    void Start() override;
	void Update() override;
	void Damage(int dmg) override;

	static int EnemyShipCount;
	
private:
    void RandTimeForShot();

	Vector2 _distToText;
	double _timeSinceShot;
	double _randTime;
	Vector2 _spawnedPos;
	Text* _hpText;
};

