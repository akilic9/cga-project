#include "Character.h"
#include "EntityManager.h"
#include "SharedContext.h"

Character::Character(EntityManager* entityManager)
	: EntityBase(entityManager)
	, m_sprite(m_entityManager->GetSharedContext()->m_textureLoader)
	, m_attackTimer(2)
	, m_attackTimeCount(0)
{
}

Character::~Character()
{
}

void Character::Move(sf::Vector2f& movement, Direction direction)
{
	m_sprite.SetSpriteDirection(direction);
	EntityBase::Move(movement);
}

void Character::Die()
{
}

void Character::Shoot()
{
}

void Character::LoadCharacterSpecs()
{
}

void Character::Update(float deltaTime)
{
}

void Character::Render(sf::RenderWindow* window)
{
}
