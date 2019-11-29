#pragma once
#include "../../Engine/GameObject.h"

class laser : public GameObject
{
public:
	laser(const char* name, Sprite* sprite, int speed, Vector2* pos, Vector2* scale);
	~laser();
	void Update() override;
	void OnTriggerEnter(GameObject* other) override;
private:
	double laserSpeed;
};

