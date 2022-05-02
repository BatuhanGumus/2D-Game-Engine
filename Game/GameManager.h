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
	GameManager();

	void RestartGame();
	void BeginGame();
	
	void SpawnEnemyWave();
	void DeleteAllEnemies();
	void SpawnPlayer();
	void CheckGameState();
	void PlayerDiedCall();
	bool getGameState();
	void removeEnemyShip(EnemyShip* ship);

    void Start() override;
	void Update() override;

	static GameManager* instance;

private:
	int _waveCount;
	Text *_gameOverText, *_waveText, *_restartInfo, *_beginInfo, *_titleText;
	EnemyShip** _enemyShips;
	Sprite* enemySprite;
	bool _gameEnded, _gameBegun;
};
