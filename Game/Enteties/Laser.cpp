#include "Laser.h"
#include "../../Engine/Time.h"
#include "../../Engine/RigidBody.h"

laser::laser(const char* name, Sprite* sprite, int speed, Vector2* pos, Vector2* scale) :
GameObject(name, sprite, new Transform(pos, scale), Default)
{
	laserSpeed = speed * Time::fixedDeltaTime;
	new RigidBody(this, 0, 1, false, new BoxCollider(sprite));
}

laser::~laser()
{
	
}

void laser::Update()
{
	rigidBody->velocity.y = laserSpeed;

	if (transform->position->y > 4)
	{
		delete this;
	}
}

void laser::OnTriggerEnter(GameObject* other)
{
	if (other->name == "enemyShip")
	{
		delete other;
	}
}

