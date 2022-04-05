#include "PlayerShip.h"
#include "Input.h"
#include "Time.h"
#include "Laser.h"
#include "RigidBody.h"
#include "SpriteRenderer.h"
#include "Engine.h"

PlayerShip::PlayerShip() : Ship()
{
	speed = 1.3 * Time::fixedDeltaTime;
	laserSprite = Sprite::GetSprite("PlayerLaser");
	maxhp = 5;
	hp = maxhp;

	playerHpText = new Text(std::to_string(hp) + "/" + std::to_string(maxhp), { 100,100,150,255 }, "Cut_Deep", 2.5, Vector2(-3.2, -2.5));

}

void PlayerShip::Start()
{
    rigidBody = gameObject->GetComponent<RigidBody>();
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
            GameObject* temp = new GameObject("PlayerLaser", new Transform( new Vector2(*transform->position), new Vector2(1, 1)));
            temp->AddComponent(new SpriteRenderer(laserSprite));
            temp->AddComponent(new RigidBody(0.2f, 1, false, new BoxCollider(laserSprite)));
            temp->AddComponent(new Laser(15));

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

	playerHpText->text = std::to_string(hp) + "/" + std::to_string(maxhp);
	
	if (hp <= 0)
	{
		GameManager::instance->PlayerDiedCall();
		delete playerHpText;
		Engine::Destroy(gameObject);
	}
	
}