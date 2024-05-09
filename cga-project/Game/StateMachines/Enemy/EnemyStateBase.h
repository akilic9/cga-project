#pragma once
#include "../../Engine/StateBase.h"

class EnemyStateManager;

class EnemyStateBase : public StateBase
{
public:
    EnemyStateBase(const std::string& name, const int& id, EnemyStateManager* stateManager);
    ~EnemyStateBase();

    virtual void OnCreate();
    virtual void OnEnter();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void OnExit();
    virtual void OnDelete();

protected:
    EnemyStateManager* m_stateManager;
};

