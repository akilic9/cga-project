#include "Enemy.h"

Enemy::Enemy(EntityManager* entityManager)
    : Character(entityManager)
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
