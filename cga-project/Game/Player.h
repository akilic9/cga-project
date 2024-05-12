#pragma once
#include <unordered_map>
#include "../Engine/Character.h"
#include "../Engine/InputManager.h"
#include "../Engine/Direction.h"

class Player : public Character
{
public:
	Player(EntityManager* entityManager, EntityType type);
	~Player();

	void OnEntityCollision(EntityBase* collidingEntity) override;
    void Update(float deltaTime) override;
    void Die() override;

    void OnMovementKeyPressed(InputBinding* binding);
    void OnAttackKeyPressed(InputBinding* binding);
private:
    float m_respawnTimeCounter;
    float m_respawnTimer;
    float m_invincibleTimer;
    float m_invincibleTimeCounter;

    void Respawn();
    void LoadCharacterSpecs(const std::string& fileName) override;

    std::unordered_map<std::string, std::pair<sf::Vector2f, Direction>> m_inputToMovement {{"player_move_left" , {sf::Vector2f(-1.f,  0.f), Direction::Left}},
                                                                                           {"player_move_up"   , {sf::Vector2f( 0.f, -1.0f), Direction::Up}},
                                                                                           {"player_move_right", {sf::Vector2f( 1.f,  0.f), Direction::Right}},
                                                                                           {"player_move_down" , {sf::Vector2f( 0.f,  1.f), Direction::Down}}};
};