#include "EnemyIdle.h"
#include "EnemyStateManager.h"
#include "../../Enemy.h"

EnemyIdle::EnemyIdle(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy)
    : EnemyStateBase(name, id, stateManager, enemy)
    , m_cooldownTimer(0.f)
    , m_cooldownCounter(0.f) {}

EnemyIdle::~EnemyIdle() {}

void EnemyIdle::OnCreate()
{
    m_cooldownTimer = m_parent->GetIdleCooldownTimer();
}

void EnemyIdle::OnEnter()
{
    m_cooldownCounter = 0.f;
}

void EnemyIdle::Update(float deltaTime)
{
    if (m_cooldownCounter < m_cooldownTimer) {
        m_cooldownCounter += deltaTime;
    }
    else
        m_stateManager->SwitchState("Attack");
}

void EnemyIdle::Render() {}

void EnemyIdle::OnExit() {}

void EnemyIdle::OnDelete() {}