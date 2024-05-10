#pragma once
#include "../Engine/Character.h"
#include "StateMachines/Enemy/EnemyStateManager.h"

class EnemyStateManager;

enum class EnemyTarget {
    None,
    Player,
    Base,
    Run
};

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
    inline float& GetSerialShootingTimer() { return m_serialShootingTimer; }
    inline float& GetIdleCooldownTimer() { return m_idleCooldownTimer; }

    inline void SetBhvrState(EnemyTarget state) { if (m_bhvrState == state) return; m_bhvrState = state; }
    inline void SetPlayerPos(sf::Vector2f pos) { if (m_playerLocation == pos) return; m_playerLocation = pos; }
    inline void SetBasePos(sf::Vector2f& pos) { if (m_baseLocation == pos) return; m_baseLocation = pos; }

private:
    sf::Vector2f m_playerLocation;
    sf::Vector2f m_baseLocation;
    EnemyStateManager m_bhvrManager;
    EnemyTarget m_bhvrState;
    float m_serialShootingTimer; //Helps give the player a break.
    float m_idleCooldownTimer; //Helps give the player a break.

    void LoadCharacterSpecs(const std::string& fileName) override;
};

