#include "Physics.h"
#include <cmath>
#include "GameTime.h"
#include <algorithm>
#include "Debug.h"

using namespace ArtemisEngine;

std::vector<RigidBody*> Physics::bodies;
std::queue<RigidBody*> Physics::bodiesToAdd;

Physics::Physics()
= default;

Physics::~Physics()
= default;

void Physics::Update()
{
    const auto checkNew = false;

	for (auto & body : bodies)
	{
		ApplyPhysics(body);
        if(!checkNew) CheckCollisionOld(body);
	}

    if(checkNew) CheckCollision();
}

void Physics::ApplyPhysics(RigidBody* body)
{
	ApplyRules(body);
	*body->gameObject->transform->position += body->velocity;
}

void Physics::ApplyRules(RigidBody* body) const
{
	if (body->gameObject->type == Static)
	{
		return;
	}

	if (body->useGravity)
	{
        body->velocity += _gravity * GameTime::fixedDeltaTime;
	}

	if (Vector2::Magnitude(body->velocity) < body->drag  * GameTime::fixedDeltaTime)
	{
		body->velocity = 0;
	}
	else
	{
		body->velocity -= Vector2::Normalize(body->velocity) * body->drag  * GameTime::fixedDeltaTime;
	}

	if (body->maxSpeed != 0 && Vector2::Magnitude(body->velocity) > body->maxSpeed)
	{
		body->velocity = Vector2::Normalize(body->velocity) * body->maxSpeed;
	}
}

void Physics::CheckCollision()
{
    std::vector<RigidBody*> collidedThisFrame;
    int bodyCount =  bodies.size();
    for (int body1ID = 0; body1ID < bodyCount - 1; ++body1ID)
    {
        auto & body1 = bodies[body1ID];

        const auto body1PosX = body1->gameObject->transform->position->x;
        const auto body1PosY = body1->gameObject->transform->position->y;
        const auto body1ToRight = (body1->collider->width / 2) * body1->gameObject->transform->scale->x ;
        const auto body1ToUp = (body1->collider->height  / 2) * body1->gameObject->transform->scale->y ;

        std::unique_ptr<const Vector2> body1Points[] =
        {
                std::make_unique<const Vector2>(body1PosX + body1ToRight, body1PosY + body1ToUp), // top right
                std::make_unique<const Vector2>(body1PosX + body1ToRight, body1PosY - body1ToUp), // bottom right
                std::make_unique<const Vector2>(body1PosX - body1ToRight, body1PosY - body1ToUp), // bottom left
                std::make_unique<const Vector2>(body1PosX - body1ToRight, body1PosY + body1ToUp), // top left
        };

        for (int body2ID = body1ID + 1; body2ID < bodyCount; ++body2ID)
        {
            auto & body2 = bodies[body2ID];

            const auto body2PosX = body2->transform->position->x;
            const auto body2PosY = body2->transform->position->y;
            const auto body2ToRight = (body2->collider->width/ 2) * body2->transform->scale->x ;
            const auto body2ToUp = (body2->collider->height/ 2) * body2->transform->scale->y;

            std::unique_ptr<const Vector2> body2Points[] =
            {
                    std::make_unique<const Vector2>(body2PosX + body2ToRight, body2PosY + body2ToUp), // top right
                    std::make_unique<const Vector2>(body2PosX + body2ToRight, body2PosY - body2ToUp), // bottom right
                    std::make_unique<const Vector2>(body2PosX - body2ToRight, body2PosY - body2ToUp), // bottom left
                    std::make_unique<const Vector2>(body2PosX - body2ToRight, body2PosY + body2ToUp), // top left
            };

            auto collided = false;

            for (int i = 0; i < 4 && !collided; ++i)
            {
                const auto iNext = (i + 1) % 4;
                const auto A1 = body1Points[iNext]->y - body1Points[i]->y;
                const auto B1 = body1Points[i]->x - body1Points[iNext]->x;
                const auto C1 = A1 * body1Points[i]->x + B1 * body1Points[i]->y;

                for (int j = 0; j < 4 && !collided; ++j)
                {
                    const auto jNext = (j + 1) % 4;
                    const auto A2 = body2Points[jNext]->y - body2Points[j]->y;
                    const auto B2 = body2Points[j]->x - body2Points[jNext]->x;
                    const auto C2 = A2 * body2Points[j]->x + B2 * body2Points[j]->y;

                    const auto det = A1 * B2 - A2 * B1;

                    if (det == 0)
                    {
                        // parallel
                    }
                    else {
                        const auto x = (B2 * C1 - B1 * C2) / det;
                        const auto y = (A1 * C2 - A2 * C1) / det;

                        if (
                                (abs(x - body1Points[i]->x) <= 0.05 && abs(x - body1Points[iNext]->x) <= 0.05 &&
                                 ((body1Points[i]->y <= y && y <= body1Points[iNext]->y) ||
                                  (body1Points[iNext]->y <= y && y <= body1Points[i]->y)))
                                &&
                                (abs(y - body2Points[j]->y) <= 0.05 && abs(y - body2Points[jNext]->y) <= 0.05 &&
                                 ((body2Points[j]->x <= x && x <= body2Points[jNext]->x) ||
                                  (body2Points[jNext]->x <= x && x <= body2Points[j]->x)))
                                ||
                                (abs(y - body1Points[i]->y) <= 0.05 && abs(y - body1Points[iNext]->y) <= 0.05 &&
                                 ((body1Points[i]->x <= x && x <= body1Points[iNext]->x) ||
                                  (body1Points[iNext]->x <= x && x <= body1Points[i]->x)))
                                &&
                                (abs(x - body2Points[j]->x) <= 0.05 && abs(x - body2Points[jNext]->x) <= 0.05 &&
                                 ((body2Points[j]->y <= y && y <= body2Points[jNext]->y) ||
                                  (body2Points[jNext]->y <= y && y <= body2Points[j]->y)))
                                )
                        {
                            body1->CallCollision(body2->gameObject);
                            body2->CallCollision(body1->gameObject);
                            collidedThisFrame.push_back(body1);
                            collidedThisFrame.push_back(body2);
                            collided = true;
                        }
                    }
                }
            }
        }

        if(std::find(collidedThisFrame.begin(), collidedThisFrame.end(), body1) == collidedThisFrame.end())
            body1->CallCollision(nullptr);
    }
}



void Physics::CheckCollisionOld(RigidBody* body1)
{
	const auto body1PosX = body1->gameObject->transform->position->x;
    const auto body1PosY = body1->gameObject->transform->position->y;
    const auto body1ToRight = body1->collider->width * body1->gameObject->transform->scale->x / 2;
    const auto body1ToUp = body1->collider->height * body1->gameObject->transform->scale->y / 2;

    std::unique_ptr<const Vector2> body1Points[] =
            {
                    std::make_unique<const Vector2>(body1PosX + body1ToRight, body1PosY + body1ToUp), // top right
                    std::make_unique<const Vector2>(body1PosX + body1ToRight, body1PosY - body1ToUp), // bottom right
                    std::make_unique<const Vector2>(body1PosX - body1ToRight, body1PosY - body1ToUp), // bottom left
                    std::make_unique<const Vector2>(body1PosX - body1ToRight, body1PosY + body1ToUp), // top left
            };

    auto collided = false;

	for (auto & otherBody : bodies)
	{
		if (&otherBody->gameObject == &body1->gameObject)
		{
			continue;
		}

        const auto body2PosX = otherBody->transform->position->x;
        const auto body2PosY = otherBody->transform->position->y;
        const auto body2ToRight = otherBody->collider->width * otherBody->transform->scale->x / 2;
        const auto body2ToUp = otherBody->collider->height * otherBody->transform->scale->y / 2;

        std::unique_ptr<const Vector2> body2Points[] =
                {
                        std::make_unique<const Vector2>(body2PosX + body2ToRight, body2PosY + body2ToUp), // top right
                        std::make_unique<const Vector2>(body2PosX + body2ToRight, body2PosY - body2ToUp), // bottom right
                        std::make_unique<const Vector2>(body2PosX - body2ToRight, body2PosY - body2ToUp), // bottom left
                        std::make_unique<const Vector2>(body2PosX - body2ToRight, body2PosY + body2ToUp), // top left
                };

		for (int j = 0; j < 4; j++)
		{
            const auto jNext = (j + 1) % 4;
            const auto A1 = body1Points[jNext]->y - body1Points[j]->y;
            const auto B1 = body1Points[j]->x - body1Points[jNext]->x;
            const auto C1 = A1 * body1Points[j]->x + B1 * body1Points[j]->y;

			for (int k = 0; k < 4; k++)
			{
                const auto kNext = (k + 1) % 4;
                const auto A2 = body2Points[kNext]->y - body2Points[k]->y;
                const auto B2 = body2Points[k]->x - body2Points[kNext]->x;
                const auto C2 = A2 * body2Points[k]->x + B2 * body2Points[k]->y;

                const auto det = A1 * B2 - A2 * B1;

				if (det == 0)
				{
					// parallel
				}
				else
				{
                    const auto x = (B2 * C1 - B1 * C2) / det;
                    const auto y = (A1 * C2 - A2 * C1) / det;

					if (
						( abs(x - body1Points[j]->x) <= 0.05 && abs(x - body1Points[jNext]->x) <= 0.05 &&
						((body1Points[j]->y <= y && y <= body1Points[jNext]->y) || (body1Points[jNext]->y <= y && y <= body1Points[j]->y)))
						&&
						(abs(y - body2Points[k]->y) <= 0.05 && abs(y - body2Points[kNext]->y) <= 0.05 &&
						((body2Points[k]->x <= x && x <= body2Points[kNext]->x) || (body2Points[kNext]->x <= x && x <= body2Points[k]->x)))
						||
						(abs(y - body1Points[j]->y) <= 0.05 && abs(y - body1Points[jNext]->y) <= 0.05 &&
						((body1Points[j]->x <= x && x <= body1Points[jNext]->x) || (body1Points[jNext]->x <= x && x <= body1Points[j]->x)))
						&&
						(abs(x - body2Points[k]->x) <= 0.05 && abs(x - body2Points[kNext]->x) <= 0.05 &&
						((body2Points[k]->y <= y && y <= body2Points[kNext]->y) || (body2Points[kNext]->y <= y && y <= body2Points[k]->y)))
						)
					{
						if (!collided)
						{
                            body1->CallCollision(otherBody->gameObject);
						}

						collided = true;
					}
				}

				if (collided)
				{
					break;
				}

			} // end of other objects corners

		} // end of main objects corners

	} // end of other bodies

	if (!collided)
	{
        body1->CallCollision(nullptr);
	}

}

void Physics::RigidBodyCreated(RigidBody *rigidBody)
{
    bodiesToAdd.push(rigidBody);
}


void Physics::RigidBodyDeleted(RigidBody *rigidBody)
{
    if (auto found = std::find(bodies.begin(), bodies.end(), rigidBody); found != bodies.end())
    {
        bodies.erase(found);
    }
}

void Physics::UpdateBodyList()
{
    while(!bodiesToAdd.empty())
    {
        bodies.push_back(bodiesToAdd.front());
        bodiesToAdd.pop();
    }
}

