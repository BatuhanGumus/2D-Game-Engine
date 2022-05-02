#include <algorithm>
#include "Event.h"

void ArtemisEngine::Event::AddListener(std::function<void()> listener)
{
    listeners.push_back(listener);
}

void ArtemisEngine::Event::RemoveListener(std::function<void()> listener)
{
/*
    auto found = std::find(listeners.begin(), listeners.end(), listener);
    if (found != listeners.end())
    {
        listeners.erase(found);
    }
*/
}

void ArtemisEngine::Event::Invoke()
{
    int len = listeners.size();
    for (int i = 0; i < len; ++i)
    {
        listeners[i]();
    }
}

void ArtemisEngine::Event::operator+=(std::function<void()> listener)
{
    AddListener(listener);
}

void ArtemisEngine::Event::operator-=(std::function<void()> listener)
{
    RemoveListener(listener);
}
