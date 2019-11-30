#include "EnemyShip.h"
#include "cstdlib"
#include "../../Engine/Time.h"
#include "Laser.h"

int EnemyShip::EnemyShipCount = 0;
Sprite* EnemyShip::laserSprite = nullptr;

EnemyShip::EnemyShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) :
Ship(name, sprite, pos, scale)
{
	maxhp = 3;
	hp = maxhp;
	distToText = * new Vector2(0, 0.4);
	hpText = new Text(std::to_string(hp) + "/" + std::to_string(maxhp), { 255,255,255,255 }, "Cut_Deep", 1, *pos + distToText);
	EnemyShipCount++;
	delete laserSprite;
	laserSprite = new Sprite("Game/Assets/PNG/Lasers/laserRed05.png", 37, 9);
	RandTimeForShot();
}

EnemyShip::~EnemyShip()
{
	delete hpText;
}

void EnemyShip::Update()
{
	if (timeSinceShot < randTime)
	{
		timeSinceShot += Time::fixedDeltaTime;
	}
	else
	{
		timeSinceShot = 0;
		RandTimeForShot();

		new laser("EnemyLaser", laserSprite, -7, new Vector2(*transform->position), new Vector2(1, 1));
	}
}

void EnemyShip::Damage(int dmg)
{
	hp -= dmg;

	hpText->text = std::to_string(hp) + "/" + std::to_string(maxhp);

	if (hp <= 0)
	{
		EnemyShipCount--;

		if (EnemyShipCount <= 0)
		{
			new Text("WON!", { 0,0,200,255 }, "Cut_Deep", 10, Vector2(0, 0));
		}

		delete this;
	}
}

void EnemyShip::RandTimeForShot()
{
	randTime = rand() * 1.0 / RAND_MAX * 1.5 + 0.3;
}
