#pragma once
#include "../Engine/EntityBase.h"
#include "../Engine/Sprite.h"

enum class OwnerEntity {
    None,
    Player,
    Enemy
};

class Bullet : public EntityBase
{
public:
    Bullet(EntityManager* entityManager, EntityType type);
    ~Bullet();

    void OnEntityCollision(EntityBase* collidingEntity) override;
    void Render(sf::RenderWindow* window) override;
    void Update(float deltaTime) override;
    
    inline OwnerEntity GetOwnerEntity() { return m_owner; }
    inline bool GetActive() { return m_active; }
    void SetOwnerEntity(OwnerEntity entity) { m_owner = entity;  }
    void SetActive(bool active) { m_active = active;  }
    void SetDirection(Direction dir) { m_sprite.SetSpriteDirection(dir); }

private:
    Sprite m_sprite;
    bool m_active;
    OwnerEntity m_owner;

    void CheckTileCollisions() override;
};

