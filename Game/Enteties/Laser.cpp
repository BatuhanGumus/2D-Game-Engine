#include "Laser.h"
#include "../../Engine/Time.h"

laser::laser(const char* name, Sprite* sprite, int speed, Vector2* pos, Vector2* scale) :
GameObject(name, sprite, new Transform(pos, scale), Default)
{
	laserSpeed = speed * Time::fixedDeltaTime;
	rb = new RigidBody(this, 0, 1, false, new BoxCollider(sprite));
}

laser::~laser()
{
}

void laser::Update()
{
	rb->velocity.y = laserSpeed;
}
