#include "Engine.h"
#include "GameObject.h"
#include <iostream>
#include <utility>

using namespace ArtemisEngine;

GameObject::GameObject(std::string name, Transform* transform, GameObjectType type)
{
    this->transform = transform;

    this->name = std::move(name);
    this->type = type;

    Engine::GameObjectCreated(this);
}

void GameObject::OnTrigger(GameObject* other)
{
    for (auto & component : components) {
        component->OnTrigger(other);
    }
}

void GameObject::OnTriggerEnter(GameObject* other)
{
    for (auto & component : components)
    {
       component->OnTriggerEnter(other);
    }
}

void GameObject::OnTriggerExit(GameObject* other)
{
    for (auto & component : components)
    {
        component->OnTriggerExit(other);
    }
}


GameObject::~GameObject()
{
    for (auto & component : components)
    {
        delete component;
    }

	delete transform;
}

void GameObject::UpdateComponents()
{
    for (auto & component : components)
    {
        component->Update();
    }
}

void GameObject::RenderComponents()
{
    for (auto & component : components)
    {
        component->Render();
    }
}

GameObject* GameObject::AddComponent(Component* component)
{
    component->gameObject = this;
    component->transform = transform;
    components.push_back(component);

    component->Start();

    return this;
}

