#pragma once
#include "../Engine/Character.h"

class Player : public Character
{
public:
	Player(EntityManager* entityManager);
	~Player();

	void OnEntityCollision(EntityBase* collidingEntity);
};