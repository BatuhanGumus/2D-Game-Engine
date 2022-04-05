#include "Laser.h"
#include "Time.h"
#include "RigidBody.h"
#include "EnemyShip.h"
#include "PlayerShip.h"
#include "Engine.h"

Laser::Laser(int speed) : Component()
{
	LaserSpeed = speed * Time::fixedDeltaTime;
}

void Laser::Start()
{
    rigidBody = gameObject->GetComponent<RigidBody>();
}



Laser::~Laser()
{
	
}

void Laser::Update()
{
	rigidBody->velocity.y = LaserSpeed;

	if (transform->position->y > 4)
	{
        Engine::Destroy(gameObject);
	}
	else if (transform->position->y < -4)
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