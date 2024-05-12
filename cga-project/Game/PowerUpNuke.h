#pragma once
#include "../Engine/EntityBase.h"
#include "../Engine/Sprite.h"
#include "../Engine/EventManager.h"

class GameState;

class PowerUpNuke : public EntityBase
{
public:
    PowerUpNuke(EntityManager* entityManager, EntityType type);
    ~PowerUpNuke();

    void OnEntityCollision(EntityBase* collidingEntity) override;
    void Render(sf::RenderWindow* window) override;
    void Update(float deltaTime) override;

    Event<GameState> m_OnCollected;

private:
    Sprite m_sprite;
};

