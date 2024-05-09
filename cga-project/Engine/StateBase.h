#pragma once
#include <string>
#include "SFML/Graphics/Text.hpp"

class StateBase
{
public:
    StateBase(const std::string& name, const int& id)
        : m_name(name)
        , m_id(id) {};
    virtual ~StateBase() {};

    virtual void OnCreate() = 0;
    virtual void OnEnter() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void OnExit() = 0;
    virtual void OnDelete() = 0;

    inline std::string GetName() const { return m_name; }

protected:
    const std::string m_name;
    int m_id;
};