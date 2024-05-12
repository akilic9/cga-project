#pragma once
#include "EntityBase.h"
#include "Sprite.h"
#include "Direction.h"

class Bullet;

enum class CharacterState {
    None,
    Dead,
    Invincible
};

class Character : public EntityBase
{
public:
	Character(EntityManager* entityManager, EntityType type);
	virtual ~Character();

	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow* window);
    virtual void Die();
    void Shoot();
    void Move(sf::Vector2f& movement, Direction& direction);

    inline CharacterState GetCurrentState() { return m_state; }

	virtual void OnEntityCollision(EntityBase* collidingEntity) = 0;

protected:
	Sprite m_sprite;
    CharacterState m_state;
	float m_attackTimer;
	float m_attackTimeCounter;
    bool m_canShoot;
    Direction m_defaultDirection;
    std::vector<Bullet*> m_bullets;

    virtual void LoadCharacterSpecs(const std::string& fileName);
};

