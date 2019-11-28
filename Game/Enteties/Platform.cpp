#include "Platform.h"
#include <iostream>

Platform::Platform(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) : GameObject(name, sprite, new Transform(pos, scale), Static)
{
	new RigidBody(this, 0, 0, false, new BoxCollider(sprite));
}

Platform::~Platform()
{
}

void Platform::OnTriggerEnter(GameObject* other)
{
	std::cout << "hello from platform" << std::endl;
}
