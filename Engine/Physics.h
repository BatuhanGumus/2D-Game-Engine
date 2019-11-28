#pragma once
#include <vector>
#include "RigidBody.h"

class Physics
{
public:
	Physics();
	~Physics();

	static std::vector<RigidBody*> bodies;

	void Update();

private:
	void ApplyPhysics(RigidBody* body);
	void ApplyRules(RigidBody* body);
	void CheckCollision(RigidBody* body);
	double gravity = -9.81;
};
