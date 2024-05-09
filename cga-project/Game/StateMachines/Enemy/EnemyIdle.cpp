#include "EnemyIdle.h"

EnemyIdle::EnemyIdle(const std::string& name, const int& id, StateManager* stateManager)
    : StateBase(name, id, stateManager)
    , m_cooldownTimer(0.f)
    , m_cooldownCounter(0.f)
    , m_playerLocation(0.f,0.f)
    , m_baseLocation(0.f,0.f)
{
}

EnemyIdle::~EnemyIdle()
{
}

void EnemyIdle::OnCreate()
{
}

void EnemyIdle::OnEnter()
{
    m_cooldownCounter = 0.f;
}

void EnemyIdle::Update(float deltaTime)
{
    if (m_cooldownCounter < m_cooldownTimer) {
        m_cooldownCounter += deltaTime;
        return;
    }


}

void EnemyIdle::Render()
{
}

void EnemyIdle::OnExit()
{
}

void EnemyIdle::OnDelete()
{
}
