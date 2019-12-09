#include "PlayerShip.h"
#include "../../Engine/Input.h"
#include "../../Engine/Time.h"
#include "Laser.h"
#include "../../Engine/SpriteManager.h"

Sprite* PlayerShip::laserSprite = nullptr;

PlayerShip::PlayerShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) : 
Ship(name, sprite, pos, scale)
{
	speed = 1.3 * Time::fixedDeltaTime;
	delete laserSprite;
	laserSprite = SpriteManager::GetSprite("PlayerLaser");
	maxhp = 20;
	hp = maxhp;

	hpText = new Text(std::to_string(hp) + "/" + std::to_string(maxhp), { 100,100,150,255 }, "Cut_Deep", 2.5, Vector2(-3.2, -2.5));
}

PlayerShip::~PlayerShip()
{

}

double timeSince = 1;
bool canShot = true;
void PlayerShip::Update()
{
	if (timeSince < 0.2)
	{
		timeSince += Time::fixedDeltaTime;
	}
	else
	{
		canShot = true;
	}

	if (Input::GetKey(SDLK_d))
	{
		acc.x += speed;
	}
	if (Input::GetKey(SDLK_a))
	{
		acc.x -= speed;
	}

	if (Input::GetKey(SDLK_SPACE))
	{
		if (canShot == true)
		{
			new laser("PlayerLaser", laserSprite, 15, new Vector2(*transform->position), new Vector2(1, 1));
			timeSince = 0;
			canShot = false;
		}
		
	}

	rigidBody->velocity += acc;
	acc.x = 0;
}

void PlayerShip::Damage(int dmg)
{
	hp -= dmg;

	hpText->text = std::to_string(hp) + "/" + std::to_string(maxhp);

	if (hp <= 0)
	{
		delete this;
	}
}
