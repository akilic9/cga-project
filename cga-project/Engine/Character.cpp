#include "Character.h"
#include "EntityManager.h"
#include "SharedContext.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Game/Bullet.h"

Character::Character(EntityManager* entityManager, EntityType type)
	: EntityBase(entityManager, type)
	, m_sprite(m_entityManager->GetSharedContext()->m_textureLoader)
    , m_state(CharacterState::None)
	, m_attackTimer(0)
	, m_attackTimeCounter(0)
    , m_canShoot(true)
    , m_defaultDirection(Direction::Down)
{
    m_bullets.reserve(5);

    for (int i = 0; i < 5; i++) {
        m_entityManager->Add(EntityType::Bullet, std::to_string((int)m_type) + "Bullet" + std::to_string(i));
        Bullet* bullet = static_cast<Bullet*>(m_entityManager->Find(std::to_string((int)m_type) + "Bullet" + std::to_string(i)));
        if (m_type == EntityType::Player)
            bullet->SetOwnerEntity(OwnerEntity::Player);
        else if (m_type == EntityType::Enemy)
            bullet->SetOwnerEntity(OwnerEntity::Enemy);

        m_bullets.push_back(bullet);
    }
}

Character::~Character() {}

void Character::Move(sf::Vector2f& movementVector, Direction& direction)
{
    if (direction != Direction::None)
	    m_sprite.SetSpriteDirection(direction);
    sf::Vector2f movementAmount = movementVector * m_movementSpeed;
	EntityBase::Move(movementAmount);
}

void Character::Die() {
    m_state = CharacterState::Dead;
}

void Character::Shoot() {
    if (!m_canShoot)
        return;

    for (auto& bullet : m_bullets)
        if (!bullet->GetActive()) {
            auto pos = m_position + (m_directionsMap[m_sprite.GetSpriteDirection()] * 2.f);
            bullet->SetDirection(m_sprite.GetSpriteDirection());
            bullet->SetPosition(pos);
            bullet->SetActive(true);
            bullet->Move(m_directionsMap[m_sprite.GetSpriteDirection()]);
        }
    
    m_attackTimeCounter = 0.f;
    m_canShoot = false;
}

void Character::LoadCharacterSpecs(const std::string& fileName)
{
	std::ifstream file;
	file.open("Game/Data/Characters/" + fileName);
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
            auto characterSize = sf::Vector2f(m_sprite.GetSpriteSize().x, m_sprite.GetSpriteSize().y);
            SetSize(characterSize);
		}
		else if (type == "MovementSpeed") {
			keystream >> m_movementSpeed;
		}
		else if (type == "AttackSpeed") {
			keystream >> m_attackTimer;
		}
        else if (type == "Direction") {
            int direction = -1;
            keystream >> direction;
            m_defaultDirection = (Direction)direction;
            m_sprite.SetSpriteDirection(m_defaultDirection);
        }
		else {
			std::cout << "Unknown specification parameter in character file: " << type << std::endl;
		}
	}
	file.close();
}

void Character::Update(float deltaTime)
{
    if (m_state == CharacterState::Dead)
        return;

    if (!m_canShoot) {
        m_attackTimeCounter += deltaTime;
        if (m_attackTimeCounter >= m_attackTimer)
            m_canShoot = true;
    }
    m_sprite.Update(deltaTime);
    m_sprite.SetSpritePosition(m_position);
	EntityBase::Update(deltaTime);
}

void Character::Render(sf::RenderWindow* window)
{
    if (m_state == CharacterState::Dead)
        return;

	m_sprite.Render(window);

#ifdef _DEBUG
    sf::RectangleShape rect = sf::RectangleShape(m_boundingBox.getSize());
    rect.setPosition(m_boundingBox.getPosition());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(2.f);
    window->draw(rect);
#endif // _DEBUG
}
