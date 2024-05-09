#pragma once
#include "../Engine/Character.h"
#include "../Engine/StateManager.h"

class Enemy : public Character
{
public:
    Enemy(EntityManager* entityManager);
    ~Enemy();

    void Update(float deltaTime) override;
    void Die() override;

    void OnEntityCollision(EntityBase* collidingEntity) override;
        
private:
    StateManager m_bhvrManager;
};

