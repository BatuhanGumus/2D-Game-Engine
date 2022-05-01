# Artemis 2D Game Engine

Artesmis is a game engine that is heavily inspired by Unity's naming conventions and architecture, written in modern C++ and with the SDL2 library.
In this repo you can also find an example space invaders type game.

### Features
The features listed below are almost identical to their Unity counterparts. To see what is different please refer to the [Seting Up a Game and Differences to Unity](#seting-up-a-game-and-differences-to-unity) section.

- Uses the Game Loop pattern and component system for its architecture.
- Contains several usefull classes like;
  - Vector2
  - Event (Observer Pattern)
  - Text (SDL2_text for UI)
  - Debug
  - Input
- Contains essential components like;
  - Tranform
  - Sprite Renderer
  - Box collider and RigidBody for collision detection

## Example Game Screenshots

## Seting Up a Game and Differences to Unity

### Asset Loading
```cpp
void Sprite::LoadSprite(const char* textureSheet, int pixelH, int pixelW, std::string _name)
void FontManager::LoadFont(const char* fontName, const char* file, int fontSize)
```
```cpp
#include "Engine.h"
#include "FontManager.h"

using namespace ArtemisEngine;

void Engine::LoadAssets()
{
  Sprite::LoadSprite("../Game/Assets/PNG/playerShip1_blue.png", 75, 99, "Player");
	FontManager::LoadFont("Cut_Deep", "../Game/Assets/fonts/Cut_deep.otf", 20);
}
```

### GameObject and Component Creation
```cpp
```

## Building Instructions
