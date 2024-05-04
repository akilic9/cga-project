#pragma once
#include "EntityBase.h"
#include "Sprite.h"
#include "Direction.h"

class Character : public EntityBase
{
public:
	Character(EntityManager* entityManager);
	virtual ~Character();

	void Move(sf::Vector2f& movement, Direction direction);
	void Die();
	void Shoot();
	
	void LoadCharacterSpecs();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	virtual void OnEntityCollision(EntityBase* collidingEntity) = 0;

protected:
	Sprite m_sprite;
	float m_attackTimer;
	float m_attackTimeCount;
};

