#include "Engine.h"
#include "GameObject.h"
#include <iostream>

using namespace ArtemisEngine;

GameObject::GameObject(std::string name, Transform* _transform, GameObjectType type)
{
    this->transform = _transform;

    this->name = name;
    this->type = type;

    Engine::GameObjectCreated(this);
}

void GameObject::OnTrigger(GameObject* other)
{
    for (int i = 0; i < components.size(); ++i) {
        components[i]->OnTrigger(other);
    }
}

void GameObject::OnTriggerEnter(GameObject* other)
{
    for (int i = 0; i < components.size(); i++)
    {
       components[i]->OnTriggerEnter(other);
    }
}

void GameObject::OnTriggerExit(GameObject* other)
{
    for (int i = 0; i < components.size(); i++)
    {
        components[i]->OnTriggerExit(other);
    }
}


GameObject::~GameObject()
{
    for (int i = 0; i < components.size(); i++)
    {
        delete components[i];
    }

	delete transform;
}

void GameObject::UpdateComponents()
{
    for (int i = 0; i < components.size(); i++)
    {
        components[i]->Update();
    }
}

void GameObject::RenderComponents()
{
    for (int i = 0; i < components.size(); i++)
    {
        components[i]->Render();
    }
}

Component* GameObject::AddComponent(Component* component)
{
    component->gameObject = this;
    component->transform = transform;
    components.push_back(component);

    component->Start();

    return component;
}

