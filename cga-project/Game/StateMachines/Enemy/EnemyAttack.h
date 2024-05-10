#pragma once
#include "EnemyStateBase.h"
#include "../../Engine/Direction.h"
#include <unordered_map>
class EnemyAttack : public EnemyStateBase
{
public:
    EnemyAttack(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy);
    ~EnemyAttack();

    void OnCreate() override;
    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnExit() override;
    void OnDelete() override;

private:
    float m_serialShootingCounter;
    float m_serialShootTimer;

    Direction GetRandownDirection();

    std::unordered_map<Direction, sf::Vector2f> m_directionsMap = { {Direction::Down,  sf::Vector2f(0.f,  1.f)},
                                                                    {Direction::Up,    sf::Vector2f(0.f, -1.f)},
                                                                    {Direction::Left,  sf::Vector2f(-1.f, 0.f)},
                                                                    {Direction::Right, sf::Vector2f(1.f,  0.f)} };
};

