#include "Ship.h"

Ship::Ship(const char* name, Sprite* sprite, Vector2* pos, Vector2* scale) :
	GameObject(name, sprite, new Transform(pos, scale), Default)
{
	
}

Ship::~Ship()
{

}
