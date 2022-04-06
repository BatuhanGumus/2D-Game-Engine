#pragma once

#include "Transform.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Component.h"

namespace ArtemisEngine
{

    class RigidBody : public Component
    {
    public:
        RigidBody(double drag, double maxSpeed, bool useGravity, BoxCollider* collider);
        virtual ~RigidBody() override;

        void CallCollision(GameObject* other);

        double drag;
        double maxSpeed;
        bool useGravity;

        Vector2 velocity;

        BoxCollider* collider;
    private:
        GameObject* lastHit;
    };
}
