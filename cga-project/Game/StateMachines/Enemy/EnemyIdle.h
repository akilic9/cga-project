#pragma once
#include "EnemyStateBase.h"

//The enemy for this game doesn't really have an "idle" state. So this state will instead be a cooldown between transitions.
class EnemyIdle : public EnemyStateBase
{
public:
    EnemyIdle(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy);
    ~EnemyIdle();

    void OnCreate() override;
    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnExit() override;
    void OnDelete() override;

private:
    float m_cooldownTimer;
    float m_cooldownCounter;
};

