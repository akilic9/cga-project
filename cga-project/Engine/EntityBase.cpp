#include "EntityBase.h"
#include "GameMap.h"
#include "EntityManager.h"

EntityBase::EntityBase(EntityManager* entityManager)
    : m_name("")
    , m_type(EntityType::Base)
    , m_id(0)
    , m_position(0.f, 0.f)
    , m_prevPosition(m_position)
    , m_movementSpeed(5.f)
    , m_size(64.f, 64.f)
    , m_movement(0.f, 0.f)
    , m_entityManager(entityManager) {}

EntityBase::~EntityBase() {}

void EntityBase::Move(sf::Vector2f& movement)
{
    m_movement = movement;
}

void EntityBase::SetPosition(sf::Vector2f& pos)
{
    if (m_position == pos)
        return;

    m_prevPosition = m_position;
    m_position = pos;
    UpdateBoundingBox();
}

void EntityBase::SetSize(sf::Vector2f& size)
{
    if (m_size == size)
        return;

    m_size = size;
    UpdateBoundingBox();
}

void EntityBase::Update(float deltaTime)
{
    if (m_movement.x != 0 || m_movement.y != 0) {
        m_prevPosition = m_position;
        m_position += (m_movement * deltaTime);

        sf::Vector2u mapSize = m_entityManager->GetSharedContext()->m_mapManager->GetMapSize();
        unsigned int tileSize = m_entityManager->GetSharedContext()->m_mapManager->GetSheetInfo()->m_defaultTileSize.x;

        if (m_position.x < 0)
            m_position.x = 0;
        else if (m_position.x > mapSize.x * tileSize)
            m_position.x = (mapSize.x - 1) * tileSize;

        if (m_position.y < 0)
            m_position.y = 0;
        else if (m_position.y > mapSize.y * tileSize)
            m_position.y = (mapSize.y - 1) * tileSize;

        UpdateBoundingBox();
        m_movement = sf::Vector2f(0.f, 0.f);
    }

    CheckTileCollisions();
    ResolveTileCollisions();
}

void EntityBase::UpdateBoundingBox()
{
    m_boundingBox = sf::FloatRect(m_position.x - (m_size.x / 2.f), m_position.y - (m_size.y / 2.f), m_size.x, m_size.y);
}

void EntityBase::CheckTileCollisions()
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

            sf::FloatRect tileBounds(tile->m_position.x, tile->m_position.y, tileSize, tileSize);
            sf::FloatRect intersection;
            m_boundingBox.intersects(tileBounds, intersection);
            float area = intersection.width * intersection.height;
            CollisionInfo info(area, tile->m_info, tileBounds);
            m_collisions.emplace_back(info);
        }
    }
}

void EntityBase::ResolveTileCollisions()
{
    if (!m_collisions.empty()) {
        std::sort(m_collisions.begin(), m_collisions.end(), [](CollisionInfo c1, CollisionInfo c2) 
            { 
                return c1.m_area > c2.m_area; 
            });

        GameMap* gameMap = m_entityManager->GetSharedContext()->m_mapManager;
        unsigned int tileSize = gameMap->GetSheetInfo()->m_defaultTileSize.x;

        for (auto& itr : m_collisions) {
            if (!m_boundingBox.intersects(itr.m_tileBounds))
                continue;

            float xDiff = (m_boundingBox.left + (m_boundingBox.width / 2)) - (itr.m_tileBounds.left + (itr.m_tileBounds.width / 2));
            float yDiff = (m_boundingBox.top + (m_boundingBox.height / 2)) - (itr.m_tileBounds.top + (itr.m_tileBounds.height / 2));
            float resolve = 0;

            if (abs(xDiff) > abs(yDiff)) {
                if (xDiff > 0)
                    resolve = (itr.m_tileBounds.left + tileSize) - m_boundingBox.left;
                else
                    resolve = -((m_boundingBox.left + m_boundingBox.width) - itr.m_tileBounds.left);

                sf::Vector2f correction = sf::Vector2f(resolve, 0.f);
                m_position += correction;
                UpdateBoundingBox();
            }
            else {
                if (yDiff > 0)
                    resolve = (itr.m_tileBounds.top + tileSize)- m_boundingBox.top;
                else
                    resolve = -((m_boundingBox.top + m_boundingBox.height) - itr.m_tileBounds.top);

                sf::Vector2f correction = sf::Vector2f(0.f, resolve);
                m_position += correction;
                UpdateBoundingBox();
            }
        }
        m_collisions.clear();
    }
}