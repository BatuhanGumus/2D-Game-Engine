#include "RigidBody.h"
#include "Physics.h"
#include <iostream>

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
	if (other == _lastHit)
	{
		gameObject->OnTrigger(other);
	}
	else if (other == nullptr && _lastHit != nullptr)
	{
		gameObject->OnTriggerExit(_lastHit);
	}
	else if (other != nullptr && _lastHit == nullptr)
	{
		gameObject->OnTriggerEnter(other);
	}

	_lastHit = other;
}


RigidBody::~RigidBody()
{
    Physics::RigidBodyDeleted(this);
}
