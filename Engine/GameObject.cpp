#include "ArtemisEngine.h"
#include "SpriteManager.h"

GameObject::GameObject(const char* name, Sprite* sprite, Transform* _transform, GameObjectType type)
{
	this->transform = _transform;

	this->sprite = sprite;
	this->name = name;
	this->type = type;

	srcRect.w = sprite->pixelW;
	srcRect.h = sprite->pixelH;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = sprite->pixelW * transform->scale->x * ArtemisEngine::pixW / 800.0;
	destRect.h = sprite->pixelH * transform->scale->y * ArtemisEngine::pixH / 600.0;

	

	if (this->type == Static)
	{
		setDestRec();
	}
}

GameObject::GameObject(const char* name, Transform* _transform, GameObjectType type)
{
	this->transform = _transform;

	this->sprite = nullptr;
	this->name = name;
	this->type = type;

	srcRect.w = sprite->pixelW;
	srcRect.h = sprite->pixelH;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = sprite->pixelW * transform->scale->x * ArtemisEngine::pixW / 800.0;
	destRect.h = sprite->pixelH * transform->scale->y * ArtemisEngine::pixH / 600.0;

	ArtemisEngine::Monos.push_back(this);

	if (this->type == Static)
	{
		setDestRec();
	}
}

void GameObject::Update()
{
	
}

void GameObject::setDestRec()
{
	destRect.x = Vector2::cordToPixelX(transform->position->x) - srcRect.w * transform->scale->x * (ArtemisEngine::pixW / 800.0) / 2;
	destRect.y = Vector2::cordToPixelY(transform->position->y) - srcRect.h * transform->scale->y * (ArtemisEngine::pixH / 600.0) / 2;
}

void GameObject::Render()
{
	if (this->type == Default)
	{
		setDestRec();
	}
	if (sprite != nullptr)
	{
		TextureManager::Draw(sprite->Texture, srcRect, destRect);
	}
	
}

void GameObject::OnTrigger(GameObject* other)
{
	
}

void GameObject::OnTriggerEnter(GameObject* other)
{
	
}

void GameObject::OnTriggerExit(GameObject* other)
{
	
}


GameObject::~GameObject()
{
	delete transform;
	delete rigidBody;
}
