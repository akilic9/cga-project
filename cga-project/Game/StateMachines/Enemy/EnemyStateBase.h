#pragma once
#include "../../Engine/StateBase.h"

class EnemyStateManager;

class EnemyStateBase : public StateBase
{
public:
    EnemyStateBase(const std::string& name, const int& id, EnemyStateManager* stateManager)
        : StateBase(name, id)
        , m_stateManager(stateManager) {}
    ~EnemyStateBase() {}

    virtual void OnCreate() = 0;
    virtual void OnEnter() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void OnExit() = 0;
    virtual void OnDelete() = 0;

protected:
    EnemyStateManager* m_stateManager;
};

