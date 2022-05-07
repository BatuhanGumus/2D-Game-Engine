#pragma once
#include <vector>
#include "RigidBody.h"
#include <queue>
#include <memory>


namespace ArtemisEngine
{
    class Physics
    {
    public:
        Physics();
        ~Physics();

        static std::vector<RigidBody*> bodies;
        static std::queue<RigidBody*> bodiesToAdd;

        static void RigidBodyCreated(RigidBody* rigidBody);
        static void RigidBodyDeleted(RigidBody* rigidBody);
        static void UpdateBodyList();

        void Update();

    private:
        void ApplyPhysics(RigidBody* body);
        void ApplyRules(RigidBody* body) const;
        void CheckCollision();
        void CheckCollisionOld(RigidBody* body1);
        Vector2 _gravity = Vector2(0, -9.81);
    };
}


