#include "PowerUpNuke.h"
#include "../Engine/EntityManager.h"
#include "../Engine/SharedContext.h"

PowerUpNuke::PowerUpNuke(EntityManager* entityManager, EntityType type)
    : EntityBase(entityManager, type)
    , m_sprite(entityManager->GetSharedContext()->m_textureLoader)
{
    m_sprite.Load("PowerUp");
    auto characterSize = sf::Vector2f(m_sprite.GetSpriteSize().x, m_sprite.GetSpriteSize().y);
    SetSize(characterSize);
    m_position = sf::Vector2f(1050.f, 672.f);
    m_sprite.SetSpritePosition(m_position);
    UpdateBoundingBox();
}

PowerUpNuke::~PowerUpNuke()
{
}

void PowerUpNuke::OnEntityCollision(EntityBase* collidingEntity)
{
    if (collidingEntity->GetType() == EntityType::Player) {
        m_OnCollected.Notify();
    }
}

void PowerUpNuke::Render(sf::RenderWindow* window)
{
    m_sprite.Render(window);
}

void PowerUpNuke::Update(float deltaTime)
{
}
