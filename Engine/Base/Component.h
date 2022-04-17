#pragma once
#include <memory>

namespace ArtemisEngine
{
    class GameObject;
    class Transform;

    class Component
    {
    public:
        explicit Component();
        virtual ~Component();

        GameObject* gameObject;
        std::shared_ptr<Transform> transform;

        virtual void Start();
        virtual void  Update();
        virtual void  Render();

        void virtual OnTrigger(GameObject* other);

        virtual void OnTriggerEnter(GameObject* other);
        virtual void  OnTriggerExit(GameObject* other);

        template <typename DerivedType>
        DerivedType* GetDerived();

    };
}
