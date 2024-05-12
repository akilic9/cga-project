#include "Enemy.h"
#include "../../Engine/EntityManager.h"
#include "../../Engine/SharedContext.h"
#include "StateMachines/Enemy/EnemyIdle.h"
#include "StateMachines/Enemy/EnemyAttack.h"
#include "../../Engine/GameMap.h"

Enemy::Enemy(EntityManager* entityManager)
    : Character(entityManager)
    , m_bhvrManager(this)
    , m_playerLocation(0.f, 0.f)
    , m_baseLocation(0.f, 0.f)
    , m_serialShootingTimer(0.f)
    , m_idleCooldownTimer(0.f)
    , m_respawnTimeCounter(0)
    , m_respawnTimer(2.f)
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
    if (m_state == CharacterState::Dead) {
        m_respawnTimeCounter += deltaTime;
        if (m_respawnTimeCounter >= m_respawnTimer)
            Respawn();
    }

    if (m_state == CharacterState::Dead)
        return;

    m_bhvrManager.Update(deltaTime);

    if (!m_canShoot) {
        m_attackTimeCounter += deltaTime;
        if (m_attackTimeCounter >= m_attackTimer)
            m_canShoot = true;
    }
    m_sprite.Update(deltaTime);
    m_sprite.SetSpritePosition(m_position);

    if (m_movement.x != 0 || m_movement.y != 0) {
        m_prevPosition = m_position;
        m_position += (m_movement * deltaTime);

        sf::Vector2u mapSize = m_entityManager->GetSharedContext()->m_mapManager->GetMapSize();
        unsigned int tileSize = m_entityManager->GetSharedContext()->m_mapManager->GetSheetInfo()->m_defaultTileSize.x;

        if (m_position.x < 0 + (m_size.x / 2.f)) {
            m_position.x = m_size.x / 2.f;
            SetCurrentDirection(Direction::None);
        }
        else if (m_position.x > (mapSize.x * tileSize) - (m_size.x / 2.f)) {
            m_position.x = (mapSize.x * tileSize) - (m_size.x / 2.f);
            SetCurrentDirection(Direction::None);
        }

        if (m_position.y < 64.f + (m_size.y / 2.f)) {
            m_position.y = 64.f + m_size.y / 2.f;
            SetCurrentDirection(Direction::None);
        }
        else if (m_position.y > (mapSize.y * tileSize) - (m_size.y / 2.f)) {
            m_position.y = (mapSize.y * tileSize) - (m_size.y / 2.f);
            SetCurrentDirection(Direction::None);
        }

        UpdateBoundingBox();
        m_movement = sf::Vector2f(0.f, 0.f);
    }

    CheckTileCollisions();
    ResolveTileCollisions();
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

void Enemy::OnEntityCollision(EntityBase* collidingEntity)
{
    if (collidingEntity->GetType() == EntityType::Bullet &&
        static_cast<Bullet*>(collidingEntity)->GetOwnerEntity() == OwnerEntity::Player)
        Die();
}

void Enemy::SetCurrentDirection(Direction direction)
{
    if (m_currentDirection == direction) 
        return; 

    m_prevDirection = m_currentDirection;
    m_currentDirection = direction;
}

void Enemy::SetSpawnLoc(sf::Vector2f& loc)
{
    m_spawnLoc = loc;
}

void Enemy::Respawn()
{
    m_attackTimeCounter = 0;
    m_position = m_spawnLoc;
    UpdateBoundingBox();
    m_sprite.SetSpriteDirection(Direction::Down);
    m_state = CharacterState::None;
}

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

void Enemy::ResolveTileCollisions()
{
    if (!m_collisions.empty())
        SetCurrentDirection(Direction::None);
    Character::ResolveTileCollisions();
}