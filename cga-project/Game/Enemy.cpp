#include "Enemy.h"
#include "StateMachines/Enemy/EnemyStateManager.h"
#include "StateMachines/Enemy/EnemyIdle.h"

Enemy::Enemy(EntityManager* entityManager)
    : Character(entityManager)
    , m_bhvrManager(this)
    , m_playerLocation(0.f, 0.f)
    , m_baseLocation(0.f, 0.f)
{
    m_bhvrManager.RegisterState<EnemyIdle>("Idle");
    m_bhvrManager.SwitchState("Idle");
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
    if (m_state == CharacterState::Dead)
        return;

    m_bhvrManager.Update(deltaTime);
    Character::Update(deltaTime);
}

void Enemy::Render(sf::RenderWindow* window)
{
    if (m_state == CharacterState::Dead)
        return;

    m_bhvrManager.Render();
    Character::Render(window);
}

void Enemy::Die()
{
    Character::Die();
}

void Enemy::OnEntityCollision(EntityBase* collidingEntity)
{
}
