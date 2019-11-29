#include "PlayerShip.h"
#include "../../Engine/Input.h"
#include <iostream>
#include "../../Engine/Time.h"
#include "Laser.h"

PlayerShip::PlayerShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) : 
Ship(name, sprite, pos, scale)
{
	speed = 1.3 * Time::fixedDeltaTime;
	laserSprite = new Sprite("Game/Assets/PNG/Lasers/laserBlue06.png", 37, 13);
}

void PlayerShip::Update()
{
	if (Input::GetKey(SDLK_d))
	{
		acc.x += speed;
	}
	if (Input::GetKey(SDLK_a))
	{
		acc.x -= speed;
	}

	if (Input::GetKeyDown(SDLK_SPACE))
	{
		new laser("playerLaser", laserSprite, 10, new Vector2(*transform->position), new Vector2(1, 1));
	}

	rigidBody->velocity += acc;
	acc.x = 0;
}

void PlayerShip::OnTriggerEnter(GameObject* hit)
{
	std::cout << "Entered " << hit->name << std::endl;
}

void PlayerShip::OnTriggerExit(GameObject* hit)
{
	std::cout << "Exited " << hit->name << std::endl;
}

