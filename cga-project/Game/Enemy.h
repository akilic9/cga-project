#pragma once
#include "../Engine/Character.h"

class EnemyStateManager;

class Enemy : public Character
{
public:
    Enemy(EntityManager* entityManager);
    ~Enemy();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow* window) override;
    void Die() override;

    void OnEntityCollision(EntityBase* collidingEntity) override;
    
    inline sf::Vector2f& GetPlayerPos() { return m_playerLocation; }
    inline sf::Vector2f& GetBasePos() { return m_baseLocation; }

private:
    sf::Vector2f m_playerLocation;
    sf::Vector2f m_baseLocation;
    EnemyStateManager m_bhvrManager;
};

