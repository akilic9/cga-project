#include "EnemyIdle.h"
#include "EnemyStateManager.h"
#include "../../Enemy.h"

EnemyIdle::EnemyIdle(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy)
    : EnemyStateBase(name, id, stateManager, enemy)
    , m_cooldownTimer(0.f)
    , m_cooldownCounter(0.f)
{
}

EnemyIdle::~EnemyIdle()
{
}

void EnemyIdle::OnCreate()
{
}

void EnemyIdle::OnEnter()
{
    m_cooldownCounter = 0.f;
}

void EnemyIdle::Update(float deltaTime)
{
    if (m_cooldownCounter < m_cooldownTimer) {
        m_cooldownCounter += deltaTime;
        return;
    }
    else
        SelectNextState();
}

void EnemyIdle::Render()
{
}

void EnemyIdle::OnExit()
{
}

void EnemyIdle::OnDelete()
{
}

void EnemyIdle::SelectNextState()
{
    float distPlayer = 0.f;
    float distBase = 0.f;


    sf::Vector2f distVecPlayer =  m_parent->GetPlayerPos() - m_parent->GetPosition();
    sf::Vector2f distVecBase = m_parent->GetBasePos() - m_parent->GetPosition();

    distPlayer = sqrt(pow(distVecPlayer.x, 2) + pow(distVecPlayer.y, 2));
    distBase = sqrt(pow(distVecBase.x, 2) + pow(distVecBase.y, 2));

    //if (distBase <= distPlayer) //Prioritize objective play.
    //    //switch to target base
    //else
    //    //switch to chase player

    std::cout << "SelectNextState";
}
