#pragma once

#include <functional>
#include <vector>

namespace ArtemisEngine
{
    class Event
    {
    public:

        void AddListener(std::function<void()> listener);
        void RemoveListener(std::function<void()> listener);

        void Invoke();

        void operator += (std::function<void()> listener);
        void operator -= (std::function<void()> listener);

    private:
        std::vector<std::function<void()>> listeners;
    };

}

