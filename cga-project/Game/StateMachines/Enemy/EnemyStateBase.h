#pragma once
#include "../../../Engine/StateBase.h"

class EnemyStateManager;
class Enemy;

class EnemyStateBase : public StateBase
{
public:
    EnemyStateBase(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy)
        : StateBase(name, id)
        , m_stateManager(stateManager)
        , m_parent(enemy){}
    ~EnemyStateBase() {}

    virtual void OnCreate() = 0;
    virtual void OnEnter() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void OnExit() = 0;
    virtual void OnDelete() = 0;

protected:
    EnemyStateManager* m_stateManager;
    Enemy* m_parent;
};

