#include "Laser.h"
#include "GameTime.h"
#include "RigidBody.h"
#include "EnemyShip.h"
#include "PlayerShip.h"
#include "Engine.h"

Laser::Laser(int speed) : Component()
{
    _laserSpeed = speed * GameTime::fixedDeltaTime;
    _rigidBody = nullptr;
}

void Laser::Start()
{
    _rigidBody = gameObject->GetComponent<RigidBody>();
}



Laser::~Laser()
= default;

void Laser::Update()
{
    _rigidBody->velocity.y = _laserSpeed;

	if (transform->position->y > 4 || transform->position->y < -4)
	{
        Engine::Destroy(gameObject);
	}
}

void Laser::OnTriggerEnter(GameObject* other)
{
	if (gameObject->name == "PlayerLaser" && other->name == "EnemyShip")
	{
		other->GetComponent<EnemyShip>()->Damage(1);

		Engine::Destroy(gameObject);
	}
	else if (gameObject->name == "EnemyLaser" && other->name == "PlayerShip")
	{
		other->GetComponent<PlayerShip>()->Damage(1);

        Engine::Destroy(gameObject);
	}
}