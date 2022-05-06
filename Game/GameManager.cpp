#include "Engine.h"
#include "GameManager.h"

#include "EnemyShip.h"
#include "PlayerShip.h"

#include <iostream>
#include "Input.h"

#include <cmath>

#include "SDL_image.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

#include "Event.h"
#include "Debug.h"

using namespace ArtemisEngine;

GameManager* GameManager::instance = nullptr;

void Engine::Awake()
{
    (new GameObject("GameManager", new Transform(), GameObjectType::Static))->AddComponent(new GameManager());
}

void GameManager::Start()
{

}


GameManager::GameManager() : MonoBehaviour()
{
	instance = this;

	_gameEnded = false;
	_gameBegun = false;

	_waveCount = 0;

    _gameOverText = nullptr;
    _waveText = nullptr;
    _restartInfo = nullptr;

	_enemySprite = Sprite::GetSprite("Enemy");
	_enemyShips = new EnemyShip*[5];

	_titleText = new Text("SPACE SHOOTER!", { 200,200,255,255 }, "Cut_Deep", 6, Vector2(0, 0.3));
	_beginInfo = new Text("Press \"Space\" to Begin!", { 255,255,255,255 }, "Cut_Deep", 2, Vector2(0, -0.5));
}

void GameManager::Update()
{
    if (_gameEnded && Input::GetKeyDown(SDLK_r))
    {
        RestartGame();
    }
    if (!_gameBegun && Input::GetKeyDown(SDLK_SPACE))
    {
        BeginGame();
    }
    if (Input::GetKeyDown(SDLK_ESCAPE))
    {
        Debug::DrawColliders = !Debug::DrawColliders;
    }
}

void GameManager::RestartGame()
{
	SpawnPlayer();
	DeleteAllEnemies();
	SpawnEnemyWave();

	_waveCount = 1;
	_waveText->text = "Wave: " + std::to_string(_waveCount);

	delete _gameOverText;
	delete _restartInfo;

	_gameEnded = false;
}

void GameManager::BeginGame()
{
	delete _titleText;
	delete _beginInfo;

	_waveText = new Text("Wave: " + std::to_string(_waveCount),
		{ 100,100,150,255 }, "Cut_Deep", 2, Vector2(3.2, -2.5));

	SpawnPlayer();
	SpawnEnemyWave();
	_gameBegun = true;
}

void GameManager::SpawnEnemyWave()
{
	for (int i = 0; i < 5; i++)
	{
        auto temp = new GameObject("EnemyShip", new Transform(new Vector2(-2 + i, 1.8 - pow(-1, i) * 0.4), new Vector2(0.5, 0.5)));
        temp->AddComponent(new SpriteRenderer(_enemySprite));
        temp->AddComponent(new BoxCollider(_enemySprite));
        temp->AddComponent(new RigidBody(0.9, 0.3, false, temp->GetComponent<BoxCollider>()));
        temp->AddComponent(new EnemyShip(new Vector2(-2 + i, 1.8 - pow(-1, i) * 0.4)));

        _enemyShips[i] = temp->GetComponent<EnemyShip>();
    }

	_waveCount++;
	_waveText->text = "Wave: " + std::to_string(_waveCount);
}

void GameManager::DeleteAllEnemies()
{
	for (int i = 0; i < 5; i++)
	{
		if (_enemyShips[i] != nullptr)
		{
            Engine::Destroy(_enemyShips[i]->gameObject);
			_enemyShips[i] = nullptr;
		}
	}

	EnemyShip::EnemyShipCount = 0;
}

void GameManager::SpawnPlayer()
{
    auto *playerShip = new GameObject("PlayerShip", new Transform(new Vector2(0, -2.3), new Vector2(0.6, 0.6)));
    playerShip-> AddComponent(new SpriteRenderer(Sprite::GetSprite("Player")));
    playerShip-> AddComponent(new BoxCollider(Sprite::GetSprite("Player")));
    playerShip-> AddComponent(  new RigidBody(0.9, 0.3, false, playerShip->GetComponent<BoxCollider>()));
    playerShip-> AddComponent(new PlayerShip());
}

void GameManager::CheckGameState()
{
	if (EnemyShip::EnemyShipCount <= 0)
	{
		SpawnEnemyWave();
	}
}

void GameManager::PlayerDiedCall()
{
	_gameOverText = new Text("GameOver", { 200,100,100,255 }, "Cut_Deep", 8, Vector2(0, 0));
	_restartInfo = new Text("Press \"R\" to restart!", { 255,255,255,255 }, "Cut_Deep", 2, Vector2(0, -0.8));
	_gameEnded = true;
}

bool GameManager::getGameState() const
{
	return _gameEnded;
}

void GameManager::removeEnemyShip(EnemyShip* ship)
{
	for (int i = 0; i < 5; i++)
	{
		if (_enemyShips[i] == ship)
		{
			_enemyShips[i] = nullptr;
		}
	}
}

