#pragma once
#include "../Engine/Character.h"
#include "../Engine/StateManager.h"

enum class Target {
    None,
    Player,
    Objective
};

class Enemy : public Character
{
public:
    Enemy(EntityManager* entityManager);
    ~Enemy();

    void Update(float deltaTime) override;
    void Die() override;

    void OnEntityCollision(EntityBase* collidingEntity) override;

    inline void SetTarget(const Target& target) { if (target == m_target) return; m_target == target; }
    inline Target GetTarget() const { return m_target; }
        
private:
    Target m_target;
    StateManager m_bhvrManager;
};

