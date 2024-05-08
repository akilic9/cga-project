#include "Player.h"
#include "../Engine/EntityManager.h"
#include "../Engine/SceneManager.h"

Player::Player(EntityManager* entityManager)
	: Character(entityManager)
    , m_respawnTimeCounter(0)
    , m_respawnTimer(0)
    , m_invincibleTimer(0)
    , m_invincibleTimeCounter(0)
{
	m_type = EntityType::Player;
	LoadCharacterSpecs("Player.char");
    auto id = m_entityManager->GetSharedContext()->m_sceneManager->GetIdFromName("Game");

    if (id == -1) {
        std::cerr << "Cannot find id for scene name!" << __FUNCSIG__ << std::endl;
        return;
    }

    for (auto& [action, movement] : m_inputToMovement)
        m_entityManager->GetSharedContext()->m_inputManager->AddCallback(id, action, &Player::OnMovementKeyPressed, this);

    m_entityManager->GetSharedContext()->m_inputManager->AddCallback(id, "player_attack", &Player::OnMovementKeyPressed, this);
}

Player::~Player()
{
    auto id = m_entityManager->GetSharedContext()->m_sceneManager->GetIdFromName("Game");

    if (id == -1) {
        std::cerr << "Cannot find id for scene name!" << __FUNCSIG__ << std::endl;
        return;
    }

    for (auto& [action, movement] : m_inputToMovement)
        m_entityManager->GetSharedContext()->m_inputManager->RemoveCallback(id, action);

    m_entityManager->GetSharedContext()->m_inputManager->RemoveCallback(id, "player_attack");
}

void Player::OnEntityCollision(EntityBase* collidingEntity)
{
    if (m_state == CharacterState::Dead)
        return;

    if (m_state == CharacterState::Invincible && collidingEntity->GetType() == EntityType::Enemy) {
        static_cast<Character*>(collidingEntity)->Die();
        return;
    }

    m_respawnTimer = 0;
    Die();
}

void Player::OnMovementKeyPressed(InputBinding* binding)
{
    if (m_state == CharacterState::Dead)
        return;

    sf::Vector2f movementVector;
    Direction direction = Direction::None;

    movementVector = m_inputToMovement[binding->m_name].first;
    direction = m_inputToMovement[binding->m_name].second;
    Move(movementVector, direction);
}

void Player::OnAttackKeyPressed(InputBinding* binding)
{
    if (m_state == CharacterState::Dead)
        return;

    Shoot();
}

void Player::Die()
{
    m_respawnTimeCounter = 0;
    Character::Die();
}

void Player::Update(float deltaTime)
{
    if (m_state == CharacterState::Dead) {
        m_respawnTimeCounter += deltaTime;
        if (m_respawnTimeCounter >= m_respawnTimer)
            Respawn();
    }
    else
        return;

    Character::Update(deltaTime);
}

void Player::Respawn()
{
    m_attackTimeCounter = 0;
}

void Player::LoadCharacterSpecs(const std::string& fileName)
{
    Character::LoadCharacterSpecs(fileName);
    std::ifstream file;
    file.open("Game/Data/Characters" + fileName);
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
        if (type == "RespawnTimer") {
            keystream >> m_respawnTimer;
        }
        else if (type == "InvincibilityTimer") {
            keystream >> m_invincibleTimer;
        }
    }
    file.close();
}
