#include "Enemy.h"

Enemy::Enemy(EntityManager* entityManager)
    : Character(entityManager)
    , m_target(Target::None)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
}

void Enemy::Die()
{
}

void Enemy::OnEntityCollision(EntityBase* collidingEntity)
{
}
