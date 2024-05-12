#pragma once
//Source: https://github.com/ngol0/CircularSpaceOdyssey/blob/main/GameTest/src/Global/Event.h
//TODO: Expand
template<typename T>
class Event
{
public:
    Event() : m_instance(nullptr) {};
    ~Event() {};

    inline void Subscribe(T* instance, void (T::* func)())
    {
        m_instance = instance;
        m_function = func;

        auto function_pointer = std::make_pair(m_instance, m_function);

        m_observers.emplace_back(function_pointer);
    }

    inline void Unsubscribe(T* instance, void (T::* func)())
    {
        auto iter = std::remove_if(m_observers.begin(), m_observers.end(),
            [=](const auto& observer) {
                return observer.first == instance && observer.second == func;
            });

        m_observers.erase(iter, m_observers.end());
    }

    inline void Notify()
    {
        if (m_observers.size() == 0)
            return;

        for (const auto& observer : m_observers)
        {
            (observer.first->*observer.second)();
        }
    }

private:
    std::vector<std::pair<T*, void(T::*)()>> m_observers;

    T* m_instance; //instance pointer
    void(T::* m_function)(); //function pointer with TArgs arguments
};