#pragma once

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
        Transform* transform;

        virtual void Start();
        virtual void Update();
        virtual void Render();

        virtual void OnTrigger(GameObject* other);
        virtual void OnTriggerEnter(GameObject* other);
        virtual void OnTriggerExit(GameObject* other);

        template <typename DerivedType>
        DerivedType* GetDerived();

    };
}
