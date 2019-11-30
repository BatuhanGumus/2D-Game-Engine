#include "EnemyShip.h"

EnemyShip::EnemyShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) :
Ship(name, sprite, pos, scale)
{
	maxhp = 3;
	hp = maxhp;
	distToText = * new Vector2(0, 0.4);
	hpText = new Text("3/3", { 255,255,255,255 }, "Cut_Deep", 30, *pos + distToText);
}

EnemyShip::~EnemyShip()
{
	delete hpText;
}

void EnemyShip::Damage(int dmg)
{
	hp -= dmg;

	hpText->text = std::to_string(hp) + "/" + std::to_string(maxhp);

	if (hp <= 0)
	{
		delete this;
	}
}
