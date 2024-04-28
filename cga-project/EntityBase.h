#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <string>

struct TileInfo;

enum class EntityType {
    Base,
    Player,
};

struct CollisionInfo {
    CollisionInfo(float area, TileInfo* tile, const sf::FloatRect& bounds)
        : m_area(area)
        , m_tile(tile)
        , m_tileBounds(bounds)
    {}

    float m_area;
    TileInfo* m_tile;
    sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionInfo>;

class EntityManager;

class EntityBase
{
public:
    EntityBase(EntityManager* entityManager, std::string name, unsigned int id);
    virtual ~EntityBase();

    void Move(sf::Vector2f& movement);
    void SetPosition(sf::Vector2f& pos);
    void SetSize(sf::Vector2f& size);

    inline unsigned int& GetID() { return m_id; }
    inline std::string& GetName() { return m_name; }

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

    bool m_isCollidingX;
    bool m_isCollidingY;
    Collisions m_collisions;
    EntityManager* m_entityManager;

    void UpdateBoundingBox();
    void CheckCollisions();
    void ResolveCollisions();

    virtual void OnEntityCollision(EntityBase* collider) = 0;
};

