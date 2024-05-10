#pragma once
#include "EnemyStateBase.h"
class EnemyAttack : public EnemyStateBase
{
public:
    EnemyAttack(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy);
    ~EnemyAttack();

    void OnCreate() override;
    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnExit() override;
    void OnDelete() override;

private:
    float m_serialShootingCounter;
    float m_serialShootTimer;
};

