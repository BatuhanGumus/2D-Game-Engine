#include "EnemyShip.h"
#include "SDL.h"

EnemyShip::EnemyShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) :
Ship(name, sprite, pos, scale)
{
	maxhp = 3;
	hp = maxhp;
}

EnemyShip::~EnemyShip()
{

}

void EnemyShip::Damage(int dmg)
{
	hp -= dmg;

	if (hp <= 0)
	{
		delete this;
	}
}
