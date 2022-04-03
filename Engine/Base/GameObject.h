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

        GameObject(std::string name = "GameObject", Transform* _transform = new Transform(), GameObjectType type = GameObjectType::Default);
        ~GameObject();


        void virtual OnTrigger(GameObject* other);
        void virtual OnTriggerEnter(GameObject* other);
        void virtual OnTriggerExit(GameObject* other);

        void UpdateComponents();
        void RenderComponents();

        Component* AddComponent(Component* component);

        Transform* transform;
    private:


        void setDestRec();
    };


}