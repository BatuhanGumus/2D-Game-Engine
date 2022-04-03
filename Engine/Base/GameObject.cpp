#include "Engine.h"
#include "GameObject.h"


using namespace ArtemisEngine;

GameObject::GameObject(const char* name, Sprite* sprite, Transform* _transform, GameObjectType type)
{
	this->transform = _transform;

	this->sprite = sprite;
	this->name = name;
	this->type = type;

    Engine::gameObjects.push_back(this);
}

GameObject::GameObject(const char* name, Transform* _transform, GameObjectType type) : GameObject(name, nullptr, _transform, type)
{

}

void GameObject::OnTrigger(GameObject* other)
{
    for (int i = 0; i < components.size(); ++i) {
        components[i]->OnTrigger(other);
    }
}

void GameObject::OnTriggerEnter(GameObject* other)
{
    for (int i = 0; i < components.size(); ++i) {
        components[i]->OnTriggerEnter(other);
    }
}

void GameObject::OnTriggerExit(GameObject* other)
{
    for (int i = 0; i < components.size(); ++i) {
        components[i]->OnTriggerExit(other);
    }
}


GameObject::~GameObject()
{
    //todo: delete the components as well
	delete transform;
}

void GameObject::UpdateComponents()
{
    for (int i = 0; i < components.size(); ++i) {
        components[i]->Update();
    }
}

void GameObject::RenderComponents()
{
    for (int i = 0; i < components.size(); ++i) {
        components[i]->Render();
    }
}

Component* GameObject::AddComponent(Component* component)
{
    component->gameObject = this;
    component->transform = transform;
    components.push_back(component);

    return component;
}

