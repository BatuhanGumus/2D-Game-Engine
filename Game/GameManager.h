#pragma once
#include "GameManager.h"
#include "../Engine/Text.h"

class EnemyShip;
class PlayerShip;

class GameManager
{
public:
	GameManager();

	void RestartGame();
	
	void SpawnEnemyWave();
	void DeleteAllEnemies();
	void SpawnPlayer();
	void CheckGameState();
	void PlayerDiedCall();
	bool getGameState();

	static GameManager* instance;

private:
	int waveCount;
	Text *gameOverText, *waveText, *restartInfo;
	EnemyShip** enemyShips;
	PlayerShip* playerShip;
	Sprite* enemySprite;
	bool gameEnded;
};
