#pragma once
#include "EntityBase.h"
#include "Sprite.h"
#include "Direction.h"

enum class CharacterState {
    None,
    Dead,
    Invincible
};

class Character : public EntityBase
{
public:
	Character(EntityManager* entityManager);
	virtual ~Character();

	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow* window);
    virtual void Die();
    void Shoot();
    void Move(sf::Vector2f& movement, Direction& direction);

	virtual void OnEntityCollision(EntityBase* collidingEntity) = 0;

protected:
	Sprite m_sprite;
    CharacterState m_state;
	float m_attackTimer;
	float m_attackTimeCounter;
    bool m_canShoot;
    Direction m_defaultDirection;

    virtual void LoadCharacterSpecs(const std::string& fileName);
};

