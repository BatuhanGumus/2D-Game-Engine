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
	const auto mainPosX = body1->gameObject->transform->position->x;
    const auto mainPosY = body1->gameObject->transform->position->y;
    const auto mainToRight = body1->collider->width * body1->gameObject->transform->scale->x / 2;
    const auto mainToUp = body1->collider->height * body1->gameObject->transform->scale->y / 2;

    auto collided = false;

	for (auto & otherBody : bodies)
	{
		if (&otherBody->gameObject == &body1->gameObject)
		{
			continue;
		}

        const auto posX = otherBody->transform->position->x;
        const auto posY = otherBody->transform->position->y;
        const auto ToRight = otherBody->collider->width * otherBody->transform->scale->x / 2;
        const auto ToUp = otherBody->collider->height * otherBody->transform->scale->y / 2;

		for (int j = 0; j < 4; j++)
		{
			auto** mainPoints = new Vector2*[2];

			switch (j)
			{
			case 0:
				mainPoints[0] = new Vector2(mainPosX + mainToRight, mainPosY + mainToUp); // top right
				mainPoints[1] = new Vector2(mainPosX + mainToRight, mainPosY - mainToUp); // bottom right
				break;
			case 1:
				mainPoints[0] = new Vector2(mainPosX + mainToRight, mainPosY - mainToUp); // bottom right
				mainPoints[1] = new Vector2(mainPosX - mainToRight, mainPosY - mainToUp); // bottom left
				break;
			case 2:
				mainPoints[0] = new Vector2(mainPosX - mainToRight, mainPosY - mainToUp); // bottom left
				mainPoints[1] = new Vector2(mainPosX - mainToRight, mainPosY + mainToUp); // top left
				break;
			case 3:
				mainPoints[0] = new Vector2(mainPosX - mainToRight, mainPosY + mainToUp); // top left
				mainPoints[1] = new Vector2(mainPosX + mainToRight, mainPosY + mainToUp); // top right
				break;
			}

            const auto A1 = mainPoints[1]->y - mainPoints[0]->y;
            const auto B1 = mainPoints[0]->x - mainPoints[1]->x;
            const auto C1 = A1 * mainPoints[0]->x + B1 * mainPoints[0]->y;

			for (int k = 0; k < 4; k++)
			{
				auto** points = new Vector2*[2];

				switch (k)
				{
				case 0:
					points[0] = new Vector2(posX + ToRight, posY + ToUp); // top right
					points[1] = new Vector2(posX + ToRight, posY - ToUp); // bottom right
					break;
				case 1:
					points[0] = new Vector2(posX + ToRight, posY - ToUp); // bottom right
					points[1] = new Vector2(posX - ToRight, posY - ToUp); // bottom left
					break;
				case 2:
					points[0] = new Vector2(posX - ToRight, posY - ToUp); // bottom left
					points[1] = new Vector2(posX - ToRight, posY + ToUp); // top left
					break;
				case 3:
					points[0] = new Vector2(posX - ToRight, posY + ToUp); // top left
					points[1] = new Vector2(posX + ToRight, posY + ToUp); // top right
					break;
				}

                const auto A2 = points[1]->y - points[0]->y;
                const auto B2 = points[0]->x - points[1]->x;
                const auto C2 = A2 * points[0]->x + B2 * points[0]->y;

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
						( abs(x - mainPoints[0]->x) <= 0.05 && abs(x - mainPoints[1]->x) <= 0.05 &&
						((mainPoints[0]->y <= y && y <= mainPoints[1]->y) || (mainPoints[1]->y <= y && y <= mainPoints[0]->y)))
						&&
						(abs(y - points[0]->y) <= 0.05 && abs(y - points[1]->y) <= 0.05 &&
						((points[0]->x <= x && x <= points[1]->x) || (points[1]->x <= x && x <= points[0]->x)))
						||
						(abs(y - mainPoints[0]->y) <= 0.05 && abs(y - mainPoints[1]->y) <= 0.05 &&
						((mainPoints[0]->x <= x && x <= mainPoints[1]->x) || (mainPoints[1]->x <= x && x <= mainPoints[0]->x)))
						&&
						(abs(x - points[0]->x) <= 0.05 && abs(x - points[1]->x) <= 0.05 &&
						((points[0]->y <= y && y <= points[1]->y) || (points[1]->y <= y && y <= points[0]->y)))
						)
					{
						if (!collided)
						{
                            body1->CallCollision(otherBody->gameObject);
						}

						collided = true;
					}
				}

				for (int v = 0; v < 2; v++)
				{
					delete points[v];
				}

				if (collided)
				{
					break;
				}

			} // end of other objects corners

			for (int c = 0; c < 2; c++)
			{
				delete mainPoints[c];
			}

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

