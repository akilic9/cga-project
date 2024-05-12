#pragma once
#include "../Engine/Character.h"
#include "StateMachines/Enemy/EnemyStateManager.h"

class EnemyStateManager;

class Enemy : public Character
{
public:
    Enemy(EntityManager* entityManager, EntityType type);
    ~Enemy();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow* window) override;
    void Die() override;

    void OnEntityCollision(EntityBase* collidingEntity) override;
    
    inline float& GetSerialShootingTimer() { return m_serialShootingTimer; }
    inline float& GetIdleCooldownTimer() { return m_idleCooldownTimer; }
    inline Direction& GetCurrentDirection() { return m_currentDirection; }
    inline Direction& GetPrevDirection() { return m_prevDirection; }
    void SetCurrentDirection(Direction direction);
    void SetSpawnLoc(sf::Vector2f& loc);


private:
    sf::Vector2f m_playerLocation;
    sf::Vector2f m_baseLocation;
    EnemyStateManager m_bhvrManager;
    float m_serialShootingTimer; //Helps give the player a break.
    float m_idleCooldownTimer; //Helps give the player a break.
    Direction m_currentDirection;
    Direction m_prevDirection;
    sf::Vector2f m_spawnLoc;
    float m_respawnTimeCounter;
    float m_respawnTimer;

    void Respawn();
    void LoadCharacterSpecs(const std::string& fileName) override;
    void ResolveTileCollisions() override;
};

