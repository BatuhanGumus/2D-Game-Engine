#include "Laser.h"
#include "Time.h"
#include "RigidBody.h"
#include "EnemyShip.h"
#include "PlayerShip.h"

laser::laser(int speed, Vector2* pos, Vector2* scale) : Component()
{
	laserSpeed = speed * Time::fixedDeltaTime;
	//new RigidBody(this, 0, 1, false, new BoxCollider(sprite));
}

laser::~laser()
{
	
}

void laser::Update()
{
	//rigidBody->velocity.y = laserSpeed;

	if (transform->position->y > 4)
	{
		delete this;
	}
	else if (transform->position->y < -4)
	{
		delete this;
	}
}

void laser::OnTriggerEnter(GameObject* other)
{
    /*
	if (this->name == "PlayerLaser" && other->name == "enemyShip")
	{
		other->getDerived<EnemyShip>()->Damage(1);

		delete this;
	}
	else if (this->name == "EnemyLaser" && other->name == "PlayerShip")
	{
		other->getDerived<PlayerShip>()->Damage(1);

		delete this;
	}
     */
}

