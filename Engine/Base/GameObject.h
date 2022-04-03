#pragma once

#include <string>
#include "MonoBehaviour.h"
#include <Transform.h>
#include "Sprite.h"

class RigidBody;

namespace ArtemisEngine
{
    enum GameObjectType
    {
        Default,
        Static
    };

    class GameObject : public MonoBehaviour
    {
    public:
        std::string name;
        GameObjectType type;

        GameObject(const char* name, Sprite* sprite, Transform* _transform, GameObjectType type);
        GameObject(const char* name, Transform* _transform, GameObjectType type);
        ~GameObject();


        void virtual OnTrigger(GameObject* other);
        void virtual OnTriggerEnter(GameObject* other);
        void virtual OnTriggerExit(GameObject* other);

        void Update() override;
        void Render() override;

        Transform* transform;
        RigidBody* rigidBody;
        Sprite* sprite;
    private:
        SDL_Rect srcRect, destRect;

        void setDestRec();
    };


}