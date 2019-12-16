#include "../Engine/ArtemisEngine.h"
#include "../Engine/SpriteManager.h"
#include "GameManager.h"

#include "Enteties/EnemyShip.h"
#include "Enteties/PlayerShip.h"

#include <iostream>

GameManager* GameManager::instance = nullptr;

void ArtemisEngine::Awake()
{
	/*
	
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 6; j++)
		{
			new GameObject("dot_" + i, dotSprite, new Transform(new Vector2(-4 + i, -3 + j), new Vector2(0.2, 0.2)), Static);
		}
	}
	*/

	GameManager* gm = new GameManager;
}


GameManager::GameManager()
{
	instance = this;

	gameEnded = false;

	SpawnPlayer();

	waveCount = 0;
	waveText = new Text("Wave: " + std::to_string(waveCount),
		{ 100,100,150,255 }, "Cut_Deep", 2.5, Vector2(3.2, -2.5));

	enemySprite = SpriteManager::GetSprite("Enemy");
	enemyShips = new EnemyShip*[5];
	SpawnEnemyWave();
}

void GameManager::RestartGame()
{
	if (playerShip != nullptr)
	{
		delete playerShip;
	}

	SpawnPlayer();
	DeleteAllEnemies();
	SpawnEnemyWave();

	waveCount = 0;
	waveText->text = "Wave: " + std::to_string(waveCount);

	delete gameOverText;
	delete restartInfo;

	gameEnded = false;
}

void GameManager::SpawnEnemyWave()
{
	for (int i = 0; i < 5; i++)
	{
		enemyShips[i] = new EnemyShip("enemyShip", enemySprite, new Vector2(-2 + i, 1.8 - pow(-1, i) * 0.4), new Vector2(0.5, 0.5));
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
			delete enemyShips[i];
		}
	}
}

void GameManager::SpawnPlayer()
{
	playerShip = new PlayerShip("PlayerShip", SpriteManager::GetSprite("Player"), new Vector2(0, -2.3), new Vector2(0.6, 0.6));
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
