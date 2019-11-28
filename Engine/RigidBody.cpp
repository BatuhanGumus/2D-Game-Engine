#include "RigidBody.h"
#include "Physics.h"

RigidBody::RigidBody(GameObject* gameObject, double drag, double maxSpeed, bool useGravity, BoxCollider* collider) :
velocity(* new Vector2(0, 0)),
gameObject(*gameObject)
{
	this->drag = drag;
	this->maxSpeed = maxSpeed;
	this->useGravity = useGravity;
	this->collider = collider;
	Physics::bodies.push_back(this);
}

void RigidBody::CallCollision(GameObject* other)
{
	if (other == lastHit)
	{
		gameObject.OnTrigger(other);
	}
	else if (other == nullptr && lastHit != nullptr)
	{
		gameObject.OnTriggerExit(lastHit);
	}
	else if (other != nullptr && lastHit == nullptr)
	{
		gameObject.OnTriggerEnter(other);
	}

	lastHit = other;

}


RigidBody::~RigidBody()
{
}
