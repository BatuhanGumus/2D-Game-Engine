#include "MonoBehaviour.h"
#include "ArtemisEngine.h"

MonoBehaviour::MonoBehaviour()
{
	ArtemisEngine::Monos.push_back(this);
}

MonoBehaviour::~MonoBehaviour()
{
	for (int i = 0; i < ArtemisEngine::Monos.size(); i++)
	{
		if (this == ArtemisEngine::Monos[i])
		{
			ArtemisEngine::Monos.erase(ArtemisEngine::Monos.begin() + i);
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
