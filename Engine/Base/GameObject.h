#pragma once

#include <string>
#include <Transform.h>
#include "Sprite.h"
#include <vector>
#include "Component.h"

namespace ArtemisEngine
{
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

        std::vector<Component*> components;

        GameObject(const char* name, Sprite* sprite, Transform* _transform, GameObjectType type);
        GameObject(const char* name, Transform* _transform, GameObjectType type);
        ~GameObject();


        void virtual OnTrigger(GameObject* other);
        void virtual OnTriggerEnter(GameObject* other);
        void virtual OnTriggerExit(GameObject* other);

        void UpdateComponents();
        void RenderComponents();

        Component* AddComponent(Component* component);

        Transform* transform;
        Sprite* sprite;
    private:


        void setDestRec();
    };


}