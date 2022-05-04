#pragma once

#include <functional>
#include <vector>

namespace ArtemisEngine
{
    template<class Sig>
    class Event
    {
    public:

        template<typename Functor>
        void AddListener(Functor&& listener)
        {
            _listeners.template emplace_back(listener);
        }

        //void RemoveListener(std::function<void()> listener);

        void Clear()
        {
            _listeners.clear();
        }

        template<class... Args>
        void Invoke(Args&&... args)
        {
            for(auto& f : _listeners)
                f(args...);
        }

        template<typename Functor>
        void operator += (Functor&& listener)
        {
            AddListener(listener);
        }
       // void operator -= (std::function<void()> listener);

    private:
        std::vector<std::function<Sig>> _listeners;
    };

}

