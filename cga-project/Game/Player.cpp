#include "Player.h"
#include "../Engine/EntityManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/StateManager.h"

Player::Player(EntityManager* entityManager)
	: Character(entityManager)
{
	m_type = EntityType::Player;
	LoadCharacterSpecs("Player.char");
        
	//m_entityManager->GetSharedContext()->m_inputManager->AddCallback()
}

Player::~Player()
{
}

void Player::OnEntityCollision(EntityBase* collidingEntity)
{
}
