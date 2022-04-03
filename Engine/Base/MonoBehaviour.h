#pragma once

#include "GameObject.h"
#include "Component.h"
namespace ArtemisEngine
{
    class MonoBehaviour : public Component
    {
    public:
        explicit MonoBehaviour(GameObject* holderObject);
        ~MonoBehaviour();

        void Update() override;

    private:

    };
}


