#include "Physics.h"
#include "ArtemisEngine.h"
#include <iostream>
#include <cmath>
#include "Time.h"

std::vector<RigidBody*> Physics::bodies;

Physics::Physics()
{
}

Physics::~Physics()
{
}

void Physics::Update()
{
	for (int i = 0; i < bodies.size(); i++)
	{
		ApplyPhysics(bodies[i]);
	}
}

void Physics::ApplyPhysics(RigidBody* body)
{
	ApplyRules(body);
	*body->gameObject.transform->position += body->velocity;
	CheckCollision(body);
}

void Physics::ApplyRules(RigidBody* body)
{
	if (body->gameObject.type == Static)
	{
		return;
	}

	if (body->useGravity == true)
	{
		body->velocity.y += gravity * Time::fixedDeltaTime;
	}

	if (Vector2::Magnitude(body->velocity) < body->drag  * Time::fixedDeltaTime)
	{
		body->velocity = 0;
	}
	else
	{
		body->velocity -= Vector2::Normalize(body->velocity) * body->drag  * Time::fixedDeltaTime;
	}

	if (body->maxSpeed != 0 && Vector2::Magnitude(body->velocity) > body->maxSpeed)
	{
		body->velocity = Vector2::Normalize(body->velocity) * body->maxSpeed;
	}
}

void Physics::CheckCollision(RigidBody* body)
{
	double mainXpos = body->gameObject.transform->position->x;
	double mainYpos = body->gameObject.transform->position->y;
	double mainToRight = body->collider->width * body->gameObject.transform->scale->x / 2;
	double mainToUp = body->collider->height * body->gameObject.transform->scale->y / 2;

	bool collided = false;

	for (int i = 0; i < bodies.size(); i++)
	{
		if (&bodies[i]->gameObject == &body->gameObject)
		{
			continue;
		}

		
		double Xpos = bodies[i]->gameObject.transform->position->x;
		double Ypos = bodies[i]->gameObject.transform->position->y;
		double ToRight = bodies[i]->collider->width * bodies[i]->gameObject.transform->scale->x / 2;
		double ToUp = bodies[i]->collider->height * bodies[i]->gameObject.transform->scale->y / 2;

		for (int j = 0; j < 4; j++)
		{
			Vector2** mainPoints = new Vector2*[2];

			switch (j)
			{
			case 0:
				mainPoints[0] = new Vector2(mainXpos + mainToRight, mainYpos + mainToUp); // top right
				mainPoints[1] = new Vector2(mainXpos + mainToRight, mainYpos - mainToUp); // bottom right
				break;
			case 1:
				mainPoints[0] = new Vector2(mainXpos + mainToRight, mainYpos - mainToUp); // bottom right
				mainPoints[1] = new Vector2(mainXpos - mainToRight, mainYpos - mainToUp); // bottom left
				break;
			case 2:
				mainPoints[0] = new Vector2(mainXpos - mainToRight, mainYpos - mainToUp); // bottom left
				mainPoints[1] = new Vector2(mainXpos - mainToRight, mainYpos + mainToUp); // top left
				break;
			case 3:
				mainPoints[0] = new Vector2(mainXpos - mainToRight, mainYpos + mainToUp); // top left
				mainPoints[1] = new Vector2(mainXpos + mainToRight, mainYpos + mainToUp); // top right
				break;
			}

			double A1 = mainPoints[1]->y - mainPoints[0]->y;
			double B1 = mainPoints[0]->x - mainPoints[1]->x;
			double C1 = A1 * mainPoints[0]->x + B1 * mainPoints[0]->y;

			for (int k = 0; k < 4; k++)
			{
				Vector2** points = new Vector2*[2];

				switch (k)
				{
				case 0:
					points[0] = new Vector2(Xpos + ToRight, Ypos + ToUp); // top right
					points[1] = new Vector2(Xpos + ToRight, Ypos - ToUp); // bottom right
					break;
				case 1:
					points[0] = new Vector2(Xpos + ToRight, Ypos - ToUp); // bottom right
					points[1] = new Vector2(Xpos - ToRight, Ypos - ToUp); // bottom left
					break;
				case 2:
					points[0] = new Vector2(Xpos - ToRight, Ypos - ToUp); // bottom left
					points[1] = new Vector2(Xpos - ToRight, Ypos + ToUp); // top left
					break;
				case 3:
					points[0] = new Vector2(Xpos - ToRight, Ypos + ToUp); // top left
					points[1] = new Vector2(Xpos + ToRight, Ypos + ToUp); // top right
					break;
				}

				double A2 = points[1]->y - points[0]->y;
				double B2 = points[0]->x - points[1]->x;
				double C2 = A2 * points[0]->x + B2 * points[0]->y;

				double det = A1 * B2 - A2 * B1;

				if (det == 0)
				{
					// parallel
				}
				else
				{
					double x = (B2 * C1 - B1 * C2) / det;
					double y = (A1 * C2 - A2 * C1) / det;
					//std::cout << "(" << x << ", " << y << ")" << std::endl;

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
						if (collided == false)
						{
							body->CallCollision(&bodies[i]->gameObject);
						}
						
						collided = true;
					}
				}

				for (int v = 0; v < 2; v++)
				{
					delete points[v];
				}

				if (collided == true)
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

	if (collided == false)
	{
		body->CallCollision(nullptr);
	}

} // end of colision detection

