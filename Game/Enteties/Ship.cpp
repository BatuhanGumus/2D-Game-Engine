#include "Ship.h"

Ship::Ship(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) :
	GameObject(name, sprite, new Transform(pos, scale), Default)
{
	new RigidBody(this, 1, 0.3, false, new BoxCollider(sprite));
}

Ship::~Ship()
{

}
