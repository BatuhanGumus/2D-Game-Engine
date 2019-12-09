#include "../Engine/ArtemisEngine.h"
#include "../Engine/FontManager.h"
#include "../Engine/SpriteManager.h"

#include "Enteties/PlayerShip.h"
#include "Enteties/EnemyShip.h"

void ArtemisEngine::LoadAssets()
{
	SpriteManager::LoadSprite("Game/Assets/PNG/Lasers/laserRed05.png", 37, 9, "lol");
	SpriteManager::LoadSprite("Game/Assets/PNG/playerShip1_blue.png", 75, 99, "Player");
	SpriteManager::LoadSprite("Game/Assets/PNG/Enemies/enemyBlack3.png", 84, 103, "Enemy");
	SpriteManager::LoadSprite("Game/Assets/PNG/Lasers/laserBlue06.png", 37, 13, "PlayerLaser");


	FontManager::LoadFont("Cut_Deep", "Game/Assets/fonts/Cut_deep.otf", 20);
}


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
	new PlayerShip("PlayerShip", SpriteManager::GetSprite("Player"), new Vector2(0, -2.3), new Vector2(0.6, 0.6));
	
	new EnemyShip("enemyShip", SpriteManager::GetSprite("Enemy"), new Vector2(0, 1.3), new Vector2(0.5, 0.5));
	new EnemyShip("enemyShip", SpriteManager::GetSprite("Enemy"), new Vector2(1, 2.2), new Vector2(0.5, 0.5));
	new EnemyShip("enemyShip", SpriteManager::GetSprite("Enemy"), new Vector2(-1, 2.2), new Vector2(0.5, 0.5));
	new EnemyShip("enemyShip", SpriteManager::GetSprite("Enemy"), new Vector2(2, 1.6), new Vector2(0.5, 0.5));
	new EnemyShip("enemyShip", SpriteManager::GetSprite("Enemy"), new Vector2(-2, 1.6), new Vector2(0.5, 0.5));
	
}
