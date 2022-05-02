#pragma once
#include <vector>
#include "RigidBody.h"
#include <queue>

namespace ArtemisEngine
{
    class Physics
    {
    public:
        Physics();
        ~Physics();

        static std::vector<RigidBody*> bodies;
        static std::queue<RigidBody*> bodiesToAdd;
        //static std::queue<RigidBody*> bodiesToRemove;


        static void RigidBodyCreated(RigidBody* rigidBody);
        static void RigidBodyDeleted(RigidBody* rigidBody);
        static void UpdateBodyList();

        void Update();

    private:
        void ApplyPhysics(RigidBody* body);
        void ApplyRules(RigidBody* body);
        void CheckCollision(RigidBody* body);
        double gravity = -9.81;
    };
}


