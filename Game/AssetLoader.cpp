#include "Engine.h"
#include "FontManager.h"

using namespace ArtemisEngine;

void Engine::LoadAssets()
{
	Sprite::LoadSprite("../Game/Assets/PNG/Lasers/laserRed05.png", 37, 9, "EnemyLaser");
    Sprite::LoadSprite("../Game/Assets/PNG/playerShip1_blue.png", 75, 99, "Player");
    Sprite::LoadSprite("../Game/Assets/PNG/Enemies/enemyBlack3.png", 84, 103, "Enemy");
    Sprite::LoadSprite("../Game/Assets/PNG/Lasers/laserBlue06.png", 37, 13, "PlayerLaser");


	FontManager::LoadFont("Cut_Deep", "../Game/Assets/fonts/Cut_deep.otf", 20);
}