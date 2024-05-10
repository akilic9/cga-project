#include "Enemy.h"
#include "StateMachines/Enemy/EnemyIdle.h"
#include "StateMachines/Enemy/EnemyAttack.h"

Enemy::Enemy(EntityManager* entityManager)
    : Character(entityManager)
    , m_bhvrManager(this)
    , m_playerLocation(0.f, 0.f)
    , m_baseLocation(0.f, 0.f)
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

    m_bhvrManager.Update(deltaTime);
    Character::Update(deltaTime);
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

void Enemy::ResolveTileCollisions()
{
    if (!m_collisions.empty())
        OnCollidedWithTile();
    Character::ResolveTileCollisions();
}

void Enemy::OnCollidedWithTile()
{
}
