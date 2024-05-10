#pragma once
//Source: https://github.com/ngol0/CircularSpaceOdyssey/blob/main/GameTest/src/Global/Event.h
//TODO: Expand
template<typename T>
class Event
{
public:
    Event() {};
    ~Event() {};

    inline void Subscribe(T* instance, void (T::* func)())
    {
        m_observers.push_back(std::make_pair(instance, func));
    }

    inline void Unsubscribe(T* instance, void (T::* func)())
    {
        auto itr = std::find_if(m_observers.begin(), m_observers.end(), [&](auto& obs) {
                return obs.first == instance && obs.second == func;
            });
        if(itr != m_observers.end())
            m_observers.erase(itr);
    }

    inline void Notify()
    {
        if (m_observers.size() == 0) return;

        for (auto& obs : m_observers)
            (obs.first->*obs.second)();
    }

private:
    std::vector<std::pair<T*, void(T::*)()>> m_observers;
};