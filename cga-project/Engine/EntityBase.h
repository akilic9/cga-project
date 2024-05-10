#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Direction.h"
#include <string>

struct TileInfo;

//TODO: This depends on the game, how to generalize?
enum class EntityType {
    Base,
    Player,
    Enemy,
    Bullet
};

struct CollisionInfo {
    CollisionInfo(float area, TileInfo* tile, const sf::FloatRect& bounds)
        : m_area(area)
        , m_tile(tile)
        , m_tileBounds(bounds) {}

    float m_area;
    TileInfo* m_tile;
    sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionInfo>;

class EntityManager;

class EntityBase
{
public:
    EntityBase(EntityManager* entityManager);
    virtual ~EntityBase();

    virtual void Move(sf::Vector2f& movement);
    void SetPosition(sf::Vector2f& pos);
    void SetSize(sf::Vector2f& size);
    virtual void OnEntityCollision(EntityBase* collidingEntity) = 0;

    inline unsigned int GetID() const { return m_id; }
    inline std::string GetName() const { return m_name; }
    inline sf::FloatRect GetBoundingBox() const { return m_boundingBox; }
    inline sf::Vector2f GetPosition() const { return m_position; }
    inline EntityType GetType() const { return m_type; }

    inline void SetID(const unsigned int& id) { m_id = id; }
    inline void SetName(const std::string& name) { m_name = name; }

    virtual void Update(float deltaTime);
    virtual void Render(sf::RenderWindow* window) = 0;

protected:
    std::string m_name;
    EntityType m_type;
    unsigned int m_id;
    sf::Vector2f m_position;
    sf::Vector2f m_prevPosition;
    float m_movementSpeed;
    sf::Vector2f m_size;
    sf::FloatRect m_boundingBox;
    sf::Vector2f m_movement;

    Collisions m_collisions;
    EntityManager* m_entityManager;

    void UpdateBoundingBox();
    void CheckTileCollisions();
    virtual void ResolveTileCollisions();
};

