#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/RigidBody.h"

class Platform : public GameObject
{
public:
	Platform(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale);
	~Platform();

	void OnTriggerEnter(GameObject* other) override;
};
