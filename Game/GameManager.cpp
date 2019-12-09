#include "../Engine/ArtemisEngine.h"
#include "GameManager.h"

#include "Enteties/PlayerShip.h"
#include "Enteties/EnemyShip.h"

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

	GameManager();
}


GameManager::GameManager()
{
	new PlayerShip("PlayerShip", SpriteManager::GetSprite("Player"), new Vector2(0, -2.3), new Vector2(0.6, 0.6));
	SpawnEnemyWave();
}

void GameManager::SpawnEnemyWave()
{
	Sprite* temp = SpriteManager::GetSprite("Enemy");
	
	for (int i = 0; i < 5; i++)
	{
		EnemyShip* tempShip = new EnemyShip("enemyShip", temp, new Vector2(-2 + i, 1.8 - pow(-1, i) * 0.4), new Vector2(0.5, 0.5));
		tempShip->GM = this;
	}
}
