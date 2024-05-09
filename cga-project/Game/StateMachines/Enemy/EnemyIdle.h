#pragma once
#include "../../Engine/StateBase.h"

//The enemy for this game doesn't really have an "idle" state. So this state will instead be a cooldown between transitions.
class EnemyIdle : public StateBase
{
public:
    EnemyIdle(const std::string& name, const int& id, StateManager* stateManager);
    ~EnemyIdle();

    void OnCreate() override;
    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnExit() override;
    void OnDelete() override;

    void SetCooldownTime(const float& time) { if (time == m_cooldownTimer) return; m_cooldownTimer = time; }
    void SetBaseLocation(const sf::Vector2f& location) { if (location == m_baseLocation) return; m_baseLocation = location; }
    inline void SetPlayerLocation(const sf::Vector2f& location) { if (location == m_playerLocation) return; m_playerLocation = location; }

private:
    float m_cooldownTimer;
    float m_cooldownCounter;
    sf::Vector2f m_playerLocation;
    sf::Vector2f m_baseLocation;
};

