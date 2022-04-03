#pragma once
#include "GameObject.h"

using namespace ArtemisEngine;

class laser : public Component
{
public:
	laser(GameObject* holderObject, int speed, Vector2* pos, Vector2* scale);
	~laser();
	void Update() override;
	void OnTriggerEnter(GameObject* other) override;
private:
	double laserSpeed;
};

