#include "PlayerShip.h"
#include "../../Engine/Input.h"
#include "../../Engine/Time.h"
#include "Laser.h"

PlayerShip::PlayerShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) : 
Ship(name, sprite, pos, scale)
{
	speed = 1.3 * Time::fixedDeltaTime;
	laserSprite = new Sprite("Game/Assets/PNG/Lasers/laserBlue06.png", 37, 13);
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
			new laser("playerLaser", laserSprite, 15, new Vector2(*transform->position), new Vector2(1, 1));
			timeSince = 0;
			canShot = false;
		}
		
	}

	rigidBody->velocity += acc;
	acc.x = 0;
}

void PlayerShip::OnTriggerEnter(GameObject* hit)
{
	
}

void PlayerShip::OnTriggerExit(GameObject* hit)
{
	
}

