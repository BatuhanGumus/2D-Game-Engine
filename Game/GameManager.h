#pragma once
#include "GameManager.h"
#include "Text.h"
#include "MonoBehaviour.h"

using namespace ArtemisEngine;

class EnemyShip;
class PlayerShip;

class GameManager : public MonoBehaviour
{
public:
	GameManager(GameObject* holderObject);

	void RestartGame();
	void BeginGame();
	
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
	Text *gameOverText, *waveText, *restartInfo, *beginInfo, *titleText;
	EnemyShip** enemyShips;
	PlayerShip* playerShip;
	Sprite* enemySprite;
	bool gameEnded, gameBegun;
};
