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

        explicit GameObject(std::string name = "GameObject", Transform* transform = new Transform(), GameObjectType type = GameObjectType::Default);
        ~GameObject();


        void virtual OnTrigger(GameObject* other);
        void virtual OnTriggerEnter(GameObject* other);
        void virtual OnTriggerExit(GameObject* other);

        void UpdateComponents();
        void RenderComponents();

        GameObject* AddComponent(Component* component);

        template<typename type>
        type* GetComponent()
        {
            for (auto & component : components)
            {
                type* comp = dynamic_cast<type*>(component);
                if (comp != nullptr)
                {
                    return comp;
                }
            }

            return nullptr;
        }

        Transform* transform;
    private:

    };


}