#pragma once
#include "../../Engine/Vector2.h"
#include "../../Engine/Sprite.h"
#include "../../Engine/GameObject.h"
#include "Ship.h"
#include "../../Engine/Text.h"

class EnemyShip : public Ship
{
public:
	EnemyShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale);
	~EnemyShip();

	int maxhp, hp;
	void Damage(int dmg);
private:
	Text* hpText;
	Vector2 distToText;
};

