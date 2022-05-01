#include "Engine.h"
#include "GameManager.h"

#include "Enteties/EnemyShip.h"
#include "Enteties/PlayerShip.h"

#include <iostream>
#include "Input.h"

#include <math.h>

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

	gameEnded = false;
	gameBegun = false;

	waveCount = 0;

	enemySprite = Sprite::GetSprite("Enemy");
	enemyShips = new EnemyShip*[5];

	titleText = new Text("SPACE SHOOTER!", { 200,200,255,255 }, "Cut_Deep", 6, Vector2(0, 0.3));
	beginInfo = new Text("Press \"Space\" to Begin!", { 255,255,255,255 }, "Cut_Deep", 2, Vector2(0, -0.5));
}

void GameManager::Update()
{
    if (gameEnded == true && Input::GetKeyDown(SDLK_r))
    {
        RestartGame();
    }
    if (gameBegun == false && Input::GetKeyDown(SDLK_SPACE))
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

	waveCount = 1;
	waveText->text = "Wave: " + std::to_string(waveCount);

	delete gameOverText;
	delete restartInfo;

	gameEnded = false;
}

void GameManager::BeginGame()
{
	delete titleText;
	delete beginInfo;

	waveText = new Text("Wave: " + std::to_string(waveCount),
		{ 100,100,150,255 }, "Cut_Deep", 2.5, Vector2(3.2, -2.5));

	SpawnPlayer();
	SpawnEnemyWave();
	gameBegun = true;
}

void GameManager::SpawnEnemyWave()
{
	for (int i = 0; i < 5; i++)
	{
        GameObject* temp = new GameObject("EnemyShip", new Transform(new Vector2(-2 + i, 1.8 - pow(-1, i) * 0.4), new Vector2(0.5, 0.5)));
        temp->AddComponent(new SpriteRenderer(enemySprite));
        temp->AddComponent(new BoxCollider(enemySprite));
        temp->AddComponent(new RigidBody(0.9, 0.3, false, temp->GetComponent<BoxCollider>()));
        temp->AddComponent(new EnemyShip(new Vector2(-2 + i, 1.8 - pow(-1, i) * 0.4)));

        enemyShips[i] = temp->GetComponent<EnemyShip>();
    }

	waveCount++;
	waveText->text = "Wave: " + std::to_string(waveCount);
}

void GameManager::DeleteAllEnemies()
{
	for (int i = 0; i < 5; i++)
	{
		if (enemyShips[i] != nullptr)
		{
            Engine::Destroy(enemyShips[i]->gameObject);
			enemyShips[i] = nullptr;
		}
	}

	EnemyShip::EnemyShipCount = 0;
}

void GameManager::SpawnPlayer()
{
    GameObject* temp = new GameObject("PlayerShip", new Transform(new Vector2(0, -2.3), new Vector2(0.6, 0.6)));
    temp-> AddComponent(new SpriteRenderer(Sprite::GetSprite("Player")));
    temp-> AddComponent(new BoxCollider(Sprite::GetSprite("Player")));
    temp-> AddComponent(  new RigidBody(0.9, 0.3, false, temp->GetComponent<BoxCollider>()));
    temp-> AddComponent(new PlayerShip());
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
	gameOverText = new Text("GameOver", { 200,100,100,255 }, "Cut_Deep", 8, Vector2(0, 0));
	restartInfo = new Text("Press \"R\" to restart!", { 255,255,255,255 }, "Cut_Deep", 2, Vector2(0, -0.8));
	gameEnded = true;
}

bool GameManager::getGameState()
{
	return gameEnded;
}

void GameManager::removeEnemyShip(EnemyShip* ship)
{
	for (int i = 0; i < 5; i++)
	{
		if (enemyShips[i] == ship)
		{
			enemyShips[i] = nullptr;
		}
	}
}

