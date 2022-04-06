#include "EnemyShip.h"
#include "cstdlib"
#include "Time.h"
#include "Laser.h"
#include "SpriteRenderer.h"
#include "Engine.h"

int EnemyShip::EnemyShipCount = 0;

EnemyShip::EnemyShip(Vector2* pos) : Ship()
{
	maxhp = 3;
	hp = maxhp;
	
	EnemyShipCount++;
	laserSprite = Sprite::GetSprite("EnemyLaser");
	RandTimeForShot();

	//spawnedPos = *transform->position;
    //transform->position->y = pos->y + 2;
    //transform->position->x = pos->x + 0.8;

	distToText = *new Vector2(0, 0.4);
	hpText = new Text(std::to_string(hp) + "/" + std::to_string(maxhp), { 255,255,255,255 }, "Cut_Deep", 1, *pos + distToText);
}

void EnemyShip::Start()
{
    spawnedPos = *transform->position;

    rigidBody = gameObject->GetComponent<RigidBody>();
}


EnemyShip::~EnemyShip()
{
	delete hpText;
}

double sideSpeed = 2;
void EnemyShip::Update()
{
	if (timeSinceShot < randTime)
	{
		timeSinceShot += Time::fixedDeltaTime;
	}
	else if (GameManager::instance->getGameState() == false)
	{
		timeSinceShot = 0;
		RandTimeForShot();

        GameObject* temp = new GameObject("EnemyLaser", new Transform( new Vector2(*transform->position), new Vector2(1, 1)));
        temp->AddComponent(new SpriteRenderer(laserSprite));
        temp->AddComponent(new BoxCollider(laserSprite));
        temp->AddComponent(new RigidBody(0.2f, 1, false, gameObject->GetComponent<BoxCollider>()));
        temp->AddComponent(new Laser(-7));
	}
	
	double dist = Vector2::Distance(spawnedPos, *transform->position);
	if (dist > 0.05)
	{
		Vector2 dir = Vector2::Normalize(*gameObject->transform->position - spawnedPos) * -dist * Time::fixedDeltaTime * 1.5;
		rigidBody->velocity.y = dir.y;
	}
	else
	{
		rigidBody->velocity.y = 0;
	}

	if (transform->position->x - spawnedPos.x > 0.7)
	{
		sideSpeed = -2;
	}
	else if (transform->position->x - spawnedPos.x < -0.7)
	{
		sideSpeed = 2;
	}

	rigidBody->velocity.x = sideSpeed * Time::fixedDeltaTime;

	hpText->position = *transform->position + distToText;
}

void EnemyShip::Damage(int dmg)
{
	hp -= dmg;

	hpText->text = std::to_string(hp) + "/" + std::to_string(maxhp);

	if (hp <= 0)
	{
		EnemyShipCount--;

		GameManager::instance->removeEnemyShip(this);
		GameManager::instance->CheckGameState();
		
		Engine::Destroy(gameObject);
	}
}

void EnemyShip::RandTimeForShot()
{
	randTime = (rand() * 1.0 / RAND_MAX) * 1.5 + 1;
}