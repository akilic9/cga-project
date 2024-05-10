#include "EnemyAttack.h"
#include "EnemyStateManager.h"
#include "../../Enemy.h"

EnemyAttack::EnemyAttack(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy)
    : EnemyStateBase(name, id, stateManager, enemy)
    , m_serialShootingCounter(0.f)
    , m_serialShootTimer(0.f) {}

EnemyAttack::~EnemyAttack() {}

void EnemyAttack::OnCreate()
{
    m_serialShootTimer = m_parent->GetSerialShootingTimer();
}

void EnemyAttack::OnEnter() 
{
    m_serialShootingCounter = 0.f;
}

void EnemyAttack::Update(float deltaTime)
{
    if (m_parent->GetCurrentDirection() == Direction::None) {
        Direction dir = GetRandownDirection();
        if (dir == m_parent->GetPrevDirection())
            dir = GetRandownDirection();
        sf::Vector2f movementVector(m_directionsMap[dir]);
        m_parent->SetCurrentDirection(dir);
    }

    sf::Vector2f movementVector(m_directionsMap[m_parent->GetCurrentDirection()]);
    m_parent->Move(movementVector, m_parent->GetCurrentDirection());

    if (m_serialShootingCounter < m_serialShootTimer) {
        m_serialShootingCounter += deltaTime;
        return;
    }
    m_parent->Shoot();
}

void EnemyAttack::Render() {}

void EnemyAttack::OnExit() {}

void EnemyAttack::OnDelete() {}

Direction EnemyAttack::GetRandownDirection()
{
    float direction = rand() % 200;
    Direction dir = Direction::None;
    if (direction < 20.f) //TODO: Dirty hack - fix.
        dir = Direction::Up;
    else if (direction < 80.f)
        dir = Direction::Down;
    else if (direction < 140.f)
        dir = Direction::Left;
    else if (direction < 200.f)
        dir = Direction::Right;
    return dir;
}
