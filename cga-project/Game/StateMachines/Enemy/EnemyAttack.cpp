#include "EnemyAttack.h"
#include "EnemyStateManager.h"
#include "../../Enemy.h"

EnemyAttack::EnemyAttack(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy)
    : EnemyStateBase(name, id, stateManager, enemy)
    , m_serialShootingCounter(0.f)
    , m_serialShootTimer(0.f)
    , m_currentDirection(Direction::None) {}

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
    if (m_currentDirection == Direction::None) {
        m_currentDirection = (Direction)(rand() % 3);
        sf::Vector2f movementVector(m_directionsMap[m_currentDirection]);
    }

    sf::Vector2f movementVector(m_directionsMap[m_currentDirection]);
    m_parent->Move(movementVector, m_currentDirection);

    if (m_serialShootingCounter < m_serialShootTimer) {
        m_serialShootingCounter += deltaTime;
        return;
    }
    m_parent->Shoot();
}

void EnemyAttack::Render() {}

void EnemyAttack::OnExit() {}

void EnemyAttack::OnDelete() {}
