#include "../Engine/ArtemisEngine.h"
#include "../Engine/FontManager.h"
#include "../Engine/SpriteManager.h"

void ArtemisEngine::LoadAssets()
{
	SpriteManager::LoadSprite("../Game/Assets/PNG/Lasers/laserRed05.png", 37, 9, "EnemyLaser");
	SpriteManager::LoadSprite("../Game/Assets/PNG/playerShip1_blue.png", 75, 99, "Player");
	SpriteManager::LoadSprite("../Game/Assets/PNG/Enemies/enemyBlack3.png", 84, 103, "Enemy");
	SpriteManager::LoadSprite("../Game/Assets/PNG/Lasers/laserBlue06.png", 37, 13, "PlayerLaser");


	FontManager::LoadFont("Cut_Deep", "../Game/Assets/fonts/Cut_deep.otf", 20);
}