#pragma once
#include "GameManager.h"
#include "../Engine/Text.h"
#include "../Engine/MonoBehaviour.h"

class EnemyShip;
class PlayerShip;

class GameManager : public MonoBehaviour
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
	void removeEnemyShip(EnemyShip* ship);

	void Update() override;

	static GameManager* instance;

private:
	int waveCount;
	Text *gameOverText, *waveText, *restartInfo;
	EnemyShip** enemyShips;
	PlayerShip* playerShip;
	Sprite* enemySprite;
	bool gameEnded;
};
