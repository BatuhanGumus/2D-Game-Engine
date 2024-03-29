#include "EnemyShip.h"
#include "GameTime.h"
#include "Laser.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "Random.h"
#include "Debug.h"

int EnemyShip::EnemyShipCount = 0;

EnemyShip::EnemyShip(Vector2* pos) : Ship()
{
	_maxHp = 3;
	_hp = _maxHp;
	_timeSinceShot = 0;
    _randTime = 0;

	EnemyShipCount++;
	_laserSprite = Sprite::GetSprite("EnemyLaser");
	RandTimeForShot();

	//spawnedPos = *transform->position;
    //transform->position->y = pos->y + 2;
    //transform->position->x = pos->x + 0.8;

	_distToText = *new Vector2(0, 0.4);
	_hpText = new Text(std::to_string(_hp) + "/" + std::to_string(_maxHp),
                       { 255,255,255,255 },
                       "Cut_Deep", 1, *pos + _distToText);
}

void EnemyShip::Start()
{
    _spawnedPos = *transform->position;

    rigidBody = gameObject->GetComponent<RigidBody>();
}


EnemyShip::~EnemyShip()
{
	delete _hpText;
}

double sideSpeed = 2;
void EnemyShip::Update()
{
	if (_timeSinceShot < _randTime)
	{
		_timeSinceShot += GameTime::fixedDeltaTime;
	}
	else if (!GameManager::instance->getGameState())
	{
		_timeSinceShot = 0;
		RandTimeForShot();

        auto temp = new GameObject("EnemyLaser", new Transform( new Vector2(*transform->position), new Vector2(1, 1)));
        temp->AddComponent(new SpriteRenderer(_laserSprite));
        temp->AddComponent(new BoxCollider(_laserSprite));
        temp->AddComponent(new RigidBody(0.2f, 1, false, gameObject->GetComponent<BoxCollider>()));
        temp->AddComponent(new Laser(-7));
	}
	
	auto dist = Vector2::Distance(_spawnedPos, *transform->position);
	if (dist > 0.05)
	{
		Vector2 dir = Vector2::Normalize(*gameObject->transform->position - _spawnedPos) * -dist * GameTime::fixedDeltaTime * 1.5;
		rigidBody->velocity.y = dir.y;
	}
	else
	{
		rigidBody->velocity.y = 0;
	}

	if (transform->position->x - _spawnedPos.x > 0.7)
	{
		sideSpeed = -2;
	}
	else if (transform->position->x - _spawnedPos.x < -0.7)
	{
		sideSpeed = 2;
	}

	rigidBody->velocity.x = sideSpeed * GameTime::fixedDeltaTime;

	_hpText->position = *transform->position + _distToText;
}

void EnemyShip::Damage(int dmg)
{
	_hp -= dmg;

	_hpText->text = std::to_string(_hp) + "/" + std::to_string(_maxHp);

	if (_hp <= 0)
	{
		EnemyShipCount--;

		GameManager::instance->removeEnemyShip(this);
		GameManager::instance->CheckGameState();
		
		Engine::Destroy(gameObject);
	}
}

void EnemyShip::RandTimeForShot()
{
	_randTime = Random::Range(1.5, 3.5);
}