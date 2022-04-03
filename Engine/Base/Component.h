#pragma once

namespace ArtemisEngine
{
    class GameObject;

    class Component
    {
    public:
        explicit Component(GameObject* holderObject);

        GameObject* holderObject;

        void virtual Update();
        void virtual Render();

        void virtual OnTrigger(GameObject* other);
        void virtual OnTriggerEnter(GameObject* other);
        void virtual OnTriggerExit(GameObject* other);

        template <typename DerivedType>
        DerivedType* GetDerived();

    };
}
