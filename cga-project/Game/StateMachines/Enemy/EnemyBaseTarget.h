#pragma once
#include "EnemyStateBase.h"
class EnemyBaseTarget : public EnemyStateBase
{
public:
    EnemyBaseTarget(const std::string& name, const int& id, EnemyStateManager* stateManager);
    ~EnemyBaseTarget();

    void OnCreate() override;
    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnExit() override;
    void OnDelete() override;
};

