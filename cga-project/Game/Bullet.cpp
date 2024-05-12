#include "Bullet.h"
#include "../Engine/EntityManager.h"
#include "../Engine/SharedContext.h"
#include "../Engine/GameMap.h"
#include <SFML/Graphics/RectangleShape.hpp>

Bullet::Bullet(EntityManager* entityManager)
    : EntityBase(entityManager)
    , m_sprite(m_entityManager->GetSharedContext()->m_textureLoader)
    , m_active(true)
    , m_owner(OwnerEntity::None)
{
    m_type = EntityType::Bullet;
    m_sprite.Load("Bullet");
    auto characterSize = sf::Vector2f(m_sprite.GetSpriteSize().x, m_sprite.GetSpriteSize().y);
    SetSize(characterSize);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
    if (!m_active)
        return;

    m_sprite.Update(deltaTime);
    m_sprite.SetSpritePosition(m_position);

    if (m_movement.x != 0 || m_movement.y != 0) {
        m_prevPosition = m_position;
        m_position += (m_movement * deltaTime);

        sf::Vector2u mapSize = m_entityManager->GetSharedContext()->m_mapManager->GetMapSize();
        unsigned int tileSize = m_entityManager->GetSharedContext()->m_mapManager->GetSheetInfo()->m_defaultTileSize.x;

        if (m_position.x < 0 + (m_size.x / 2.f) || m_position.x >(mapSize.x * tileSize) - (m_size.x / 2.f) ||
            m_position.y < 64.f + (m_size.y / 2.f) || m_position.y >(mapSize.y * tileSize) - (m_size.y / 2.f))
            m_active = false;

        UpdateBoundingBox();
        m_movement = sf::Vector2f(0.f, 0.f);
    }

    CheckTileCollisions();
}

void Bullet::Render(sf::RenderWindow* window)
{
    if (!m_active)
        return;

    m_sprite.Render(window);

#ifdef _DEBUG
    sf::RectangleShape rect = sf::RectangleShape(m_boundingBox.getSize());
    rect.setPosition(m_boundingBox.getPosition());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(2.f);
    window->draw(rect);
#endif // _DEBUG
}


void Bullet::OnEntityCollision(EntityBase* collidingEntity)
{
    m_active = false;
}

void Bullet::CheckTileCollisions()
{
    GameMap* gameMap = m_entityManager->GetSharedContext()->m_mapManager;
    unsigned int tileSize = gameMap->GetSheetInfo()->m_defaultTileSize.x;
    int fromX = floor(m_boundingBox.left / tileSize);
    int toX = floor((m_boundingBox.left + m_boundingBox.width) / tileSize);
    int fromY = floor(m_boundingBox.top / tileSize);
    int toY = floor((m_boundingBox.top + m_boundingBox.height) / tileSize);

    for (int x = fromX; x <= toX; ++x) {
        for (int y = fromY; y <= toY; ++y) {
            Tile* tile = gameMap->GetTileByLocation(sf::Vector2f(x, y));

            if (!tile || !tile->m_info->m_isCollidable)
                continue;

            m_active = false;
        }
    }
}
