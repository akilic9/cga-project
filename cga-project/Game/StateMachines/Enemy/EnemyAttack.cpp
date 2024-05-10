#include "EnemyAttack.h"
#include "EnemyStateManager.h"
#include "../../Enemy.h"

EnemyAttack::EnemyAttack(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy)
    : EnemyStateBase(name, id, stateManager, enemy)
    , m_serialShootingCounter(0.f)
    , m_serialShootTimer(0.f) {}

EnemyAttack::~EnemyAttack() {}

void EnemyAttack::OnCreate()
{
    m_serialShootTimer = m_parent->GetSerialShootingTimer();
}

void EnemyAttack::OnEnter() 
{
    float distPlayer = 0.f;
    float distBase = 0.f;


    std::cout << m_parent->GetPosition().x << " " << m_parent->GetPosition().y << std::endl;
    sf::Vector2f distVecPlayer = m_parent->GetPlayerPos() - m_parent->GetPosition();
    std::cout << m_parent->GetPlayerPos().x << " " << m_parent->GetPlayerPos().y << std::endl;
    std::cout << distVecPlayer.x << " " << distVecPlayer.y << std::endl;
    sf::Vector2f distVecBase = m_parent->GetBasePos() - m_parent->GetPosition();
    std::cout << distVecBase.x << " " << distVecBase.y << std::endl;
    std::cout << m_parent->GetBasePos().x << " " << m_parent->GetBasePos().y << std::endl;
    distPlayer = sqrt(pow(distVecPlayer.x, 2) + pow(distVecPlayer.y, 2));
    distBase = sqrt(pow(distVecBase.x, 2) + pow(distVecBase.y, 2));

    if (distBase <= distPlayer) //Prioritize objective play.
        m_parent->SetBhvrState(EnemyTarget::Base);
    else
        m_parent->SetBhvrState(EnemyTarget::Player);

    m_serialShootingCounter = 0.f;
}

void EnemyAttack::Update(float deltaTime)
{
    if (m_serialShootingCounter < m_serialShootTimer) {
        m_serialShootingCounter += deltaTime;
        return;
    }
    m_parent->Shoot();
}

void EnemyAttack::Render() {}

void EnemyAttack::OnExit()
{
    m_parent->SetBhvrState(EnemyTarget::None);
}

void EnemyAttack::OnDelete() {}
