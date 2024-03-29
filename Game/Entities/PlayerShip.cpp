#include "PlayerShip.h"
#include "Input.h"
#include "GameTime.h"
#include "Laser.h"
#include "RigidBody.h"
#include "SpriteRenderer.h"
#include "Engine.h"

PlayerShip::PlayerShip() : Ship()
{
	_speed = 1.3 * GameTime::fixedDeltaTime;
	_laserSprite = Sprite::GetSprite("PlayerLaser");
	_maxHp = 5;
	_hp = _maxHp;

	_playerHpText = new Text(std::to_string(_hp) + "/" + std::to_string(_maxHp),
                             { 100,100,150,255 }, "Cut_Deep", 2, Vector2(-3.2, -2.5));

}

void PlayerShip::Start()
{
    rigidBody = gameObject->GetComponent<RigidBody>();
}


PlayerShip::~PlayerShip()
= default;

double timeSince = 1;
bool canShot = true;
void PlayerShip::Update()
{
	if (timeSince < 0.2)
	{
		timeSince += GameTime::fixedDeltaTime;
	}
	else
	{
		canShot = true;
	}

	if (Input::GetKey(SDLK_d))
	{
        _acceleration.x += _speed;
	}
	if (Input::GetKey(SDLK_a))
	{
        _acceleration.x -= _speed;
	}

	if (Input::GetKey(SDLK_SPACE))
	{
		if (canShot)
		{
            auto temp = new GameObject("PlayerLaser", new Transform( new Vector2(*transform->position), new Vector2(1, 1)));
            temp->AddComponent(new SpriteRenderer(_laserSprite));
            temp->AddComponent(new BoxCollider(_laserSprite));
            temp->AddComponent(new RigidBody(0.2f, 1, false, gameObject->GetComponent<BoxCollider>()));
            temp->AddComponent(new Laser(15));

			timeSince = 0;
			canShot = false;
		}
		
	}

    rigidBody->velocity += _acceleration;
    _acceleration.x = 0;
}

void PlayerShip::Damage(int dmg)
{
	_hp -= dmg;

	_playerHpText->text = std::to_string(_hp) + "/" + std::to_string(_maxHp);
	
	if (_hp <= 0)
	{
		GameManager::instance->PlayerDiedCall();
		delete _playerHpText;
		Engine::Destroy(gameObject);
	}
	
}