#pragma once

#include <string>
#include <../../CENG241Platformer/CENG241Platformer/Engine/Transform.h>
#include "Sprite.h"

enum GameObjectType
{
	Default,
	Static
};

class GameObject
{
public:
	std::string name;
	GameObjectType type;

	GameObject(const char* name, Sprite* sprite, Transform* _transform, GameObjectType type);
	~GameObject();

	void virtual Update();
	void Render();
	void virtual OnTrigger(GameObject* other);
	void virtual OnTriggerEnter(GameObject* other);
	void virtual OnTriggerExit(GameObject* other);

	Transform& transform;
private:
	Sprite* sprite;
	
	SDL_Rect srcRect, destRect;

	void setDestRec();
};

