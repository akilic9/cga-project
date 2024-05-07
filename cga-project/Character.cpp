#include "Character.h"
#include "EntityManager.h"
#include "SharedContext.h"

Character::Character(EntityManager* entityManager)
	: EntityBase(entityManager)
	, m_sprite(m_entityManager->GetSharedContext()->m_textureLoader)
	, m_attackTimer(2)
	, m_attackTimeCount(0) {}

Character::~Character() {}

void Character::Move(sf::Vector2f& movement, Direction direction)
{
	m_sprite.SetSpriteDirection(direction);
	EntityBase::Move(movement);
}

void Character::Die() {}

void Character::Shoot() {}

void Character::LoadCharacterSpecs(std::string fileName)
{
	std::ifstream file;
	file.open("Data/Characters" + fileName);
	if (!file.is_open()) {
		std::cout << "Cannot open character file: " << fileName << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '<') //Comment line.
			continue;
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "Name") {
			keystream >> m_name;
		}
		else if (type == "SpriteID") {
			std::string id;
			keystream >> id;
			m_sprite.Load(id);
		}
		else if (type == "MovementSpeed") {
			keystream >> m_movementSpeed;
		}
		else if (type == "AttackSpeed") {
			keystream >> m_attackTimer;
		}
		else {
			std::cout << "Unknown specification parameter in character file: " << type << std::endl;
		}
	}
	file.close();
}

void Character::Update(float deltaTime)
{
	EntityBase::Update(deltaTime);
}

void Character::Render(sf::RenderWindow* window)
{
	m_sprite.Render(window);
}
