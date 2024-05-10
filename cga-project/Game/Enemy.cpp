#include "Enemy.h"
#include "StateMachines/Enemy/EnemyIdle.h"
#include "StateMachines/Enemy/EnemyAttack.h"

Enemy::Enemy(EntityManager* entityManager)
    : Character(entityManager)
    , m_bhvrManager(this)
    , m_playerLocation(0.f, 0.f)
    , m_baseLocation(0.f, 0.f)
    , m_bhvrState(EnemyTarget::None)
    , m_serialShootingTimer(0.f)
    , m_idleCooldownTimer(0.f)
{
    m_type = EntityType::Enemy;
    LoadCharacterSpecs("Enemy.char");

    m_bhvrManager.RegisterState<EnemyIdle>("Idle");
    m_bhvrManager.RegisterState<EnemyAttack>("Attack");
    m_bhvrManager.SwitchState("Idle");
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
    if (m_state == CharacterState::Dead)
        return;

    sf::Vector2f movementVector(0.f, 0.f);
    Direction direction = Direction::None;

    //Aboslutely disgusting but it's 2am and I have no brain power left.
    switch (m_bhvrState)
    {
    case EnemyTarget::None:
        break;
    case EnemyTarget::Player:
        if (m_playerLocation.x < m_position.x && std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Left) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(-1.f, 0.f);
            direction = Direction::Left;
        }
        else if (m_playerLocation.y < m_position.y && std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Up) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(0.f, -1.f);
            direction = Direction::Up;
        }
        else if (std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Down) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(0.f, 1.f);
            direction = Direction::Down;
        }
        else if (std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Right) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(1.f, 0.f);
            direction = Direction::Right;
        }
        break;
    case EnemyTarget::Base:
        if (m_baseLocation.x < m_position.x && std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Left) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(-1.f, 0.f);
            direction = Direction::Left;
        }
        else if (m_baseLocation.y < m_position.y && std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Up) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(0.f, -1.f);
            direction = Direction::Up;
        }
        else if (std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Down) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(0.f, 1.f);
            direction = Direction::Down;
        }
        else if (std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Right) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(1.f, 0.f);
            direction = Direction::Right;
        }
        break;
    case EnemyTarget::Run:
        if (m_playerLocation.x < m_position.x && std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Right) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(1.f, 0.f);
            direction = Direction::Right;
        }
        else if (m_playerLocation.y > m_position.y && std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Up) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(0.f, -1.f);
            direction = Direction::Up;
        }
        else if (std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Left) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(-1.f, 0.f);
            direction = Direction::Left;
        }
        else if (std::find(m_illegalDirections.begin(), m_illegalDirections.end(), Direction::Down) == m_illegalDirections.end()) {
            movementVector = sf::Vector2f(0.f, 1.f);
            direction = Direction::Down;
        }
        break;
    default:
        break;
    }

    if (movementVector.x != 0 || movementVector.y != 0)
        Move(movementVector, direction);

    Character::Update(deltaTime);
    m_bhvrManager.Update(deltaTime);
}

void Enemy::Render(sf::RenderWindow* window)
{
    if (m_state == CharacterState::Dead)
        return;

    m_bhvrManager.Render();
    Character::Render(window);
}

void Enemy::Die()
{
    Character::Die();
}

void Enemy::OnEntityCollision(EntityBase* collidingEntity) {}

void Enemy::LoadCharacterSpecs(const std::string& fileName)
{
    Character::LoadCharacterSpecs(fileName);
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
        if (type == "SerialShootCooldown") {
            keystream >> m_serialShootingTimer;
        }
        else if (type == "IdleCooldown") {
            keystream >> m_idleCooldownTimer;
        }
    }
    file.close();
}