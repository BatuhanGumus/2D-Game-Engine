#pragma once
#include "RigidBody.h"

using namespace ArtemisEngine;

class Laser : public Component
{
public:
	Laser(int speed);
	~Laser();
    void Start() override;
	void Update() override;
	void OnTriggerEnter(GameObject* other) override;
private:
	double LaserSpeed;
    RigidBody* rigidBody;
};

