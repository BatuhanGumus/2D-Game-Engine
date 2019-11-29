#pragma once
#include "Ship.h"

class PlayerShip : public Ship
{
public:
	PlayerShip(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale);
	~PlayerShip();
	void Update() override;
	void OnTriggerEnter(GameObject* hit) override;
	void OnTriggerExit(GameObject* hit) override;

private:
	Sprite* laserSprite;
	Vector2 acc;
};