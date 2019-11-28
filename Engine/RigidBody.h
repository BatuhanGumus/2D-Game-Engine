#pragma once

#include "Transform.h"
#include "BoxCollider.h"
#include "GameObject.h"

class RigidBody
{
public:
	RigidBody(GameObject* gameObject, double drag, double maxSpeed, bool useGravity, BoxCollider* collider);
	~RigidBody();

	void CallCollision(GameObject* other);

	GameObject& gameObject;
	double drag;
	double maxSpeed;
	bool useGravity;

	Vector2& velocity;

	BoxCollider* collider;
private:
	GameObject* lastHit;
};
