#include "RigidBody.h"
#include "Physics.h"

using namespace ArtemisEngine;

RigidBody::RigidBody(double drag, double maxSpeed, bool useGravity, BoxCollider* collider)
{
	this->drag = drag;
	this->maxSpeed = maxSpeed;
	this->useGravity = useGravity;
	this->collider = collider;
	Physics::RigidBodyCreated(this);
}

void RigidBody::CallCollision(GameObject* other)
{
	if (other == lastHit)
	{
		gameObject->OnTrigger(other);
	}
	else if (other == nullptr && lastHit != nullptr)
	{
		gameObject->OnTriggerExit(lastHit);
	}
	else if (other != nullptr && lastHit == nullptr)
	{
		gameObject->OnTriggerEnter(other);
	}

	lastHit = other;

}


RigidBody::~RigidBody()
{
    Physics::RigidBodyDeleted(this);
}
