#include "PlayerShip.h"
#include "../../Engine/Input.h"
#include "../../Engine/Time.h"
#include "Laser.h"

Sprite* PlayerShip::laserSprite = nullptr;

PlayerShip::PlayerShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) : 
Ship(name, sprite, pos, scale)
{
	speed = 1.3 * Time::fixedDeltaTime;
	delete laserSprite;
	laserSprite = new Sprite("Game/Assets/PNG/Lasers/laserBlue06.png", 37, 13);
	maxhp = 6;
	hp = maxhp;

	hpText = new Text(std::to_string(hp) + "/" + std::to_string(maxhp), { 40,40,100,255 }, "Cut_Deep", 2, Vector2(-3.5, -2.7));
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
		new Text("Lost!", { 200,0,0,255 }, "Cut_Deep", 9, Vector2(0, 0));
		delete this;
	}
}
