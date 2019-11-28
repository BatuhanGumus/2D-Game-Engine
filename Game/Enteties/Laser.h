#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/RigidBody.h"


class laser : public GameObject
{
public:
	laser(const char* name, Sprite* sprite, int speed, Vector2* pos, Vector2* scale);
	~laser();
	void Update() override;
private:
	double laserSpeed;
	RigidBody* rb;
};

