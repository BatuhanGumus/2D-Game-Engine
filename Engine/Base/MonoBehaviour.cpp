#include "MonoBehaviour.h"
#include "Engine.h"

using namespace ArtemisEngine;

MonoBehaviour::MonoBehaviour()
{
	Engine::Monos.push_back(this);
}

MonoBehaviour::~MonoBehaviour()
{
	for (int i = 0; i < Engine::Monos.size(); i++)
	{
		if (this == Engine::Monos[i])
		{
			Engine::Monos.erase(Engine::Monos.begin() + i);
			break;
		}
	}
}

void MonoBehaviour::Update()
{
}

void MonoBehaviour::Render()
{
}
