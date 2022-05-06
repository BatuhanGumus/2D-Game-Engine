#pragma once
#include "RigidBody.h"

using namespace ArtemisEngine;

class Laser : public Component
{
public:
	explicit Laser(int speed);
	~Laser() override;
    void Start() override;
	void Update() override;
	void OnTriggerEnter(GameObject* other) override;
private:
	double _laserSpeed;
    RigidBody* _rigidBody;
};

