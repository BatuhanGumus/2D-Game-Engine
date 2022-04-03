#pragma once

namespace ArtemisEngine
{
    class GameObject;
    class Transform;

    class Component
    {
    public:
        explicit Component();

        GameObject* gameObject;
        Transform* transform;

        void virtual Update();
        void virtual Render();

        void virtual OnTrigger(GameObject* other);
        void virtual OnTriggerEnter(GameObject* other);
        void virtual OnTriggerExit(GameObject* other);

        template <typename DerivedType>
        DerivedType* GetDerived();

    };
}
