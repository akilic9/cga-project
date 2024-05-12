#include "GameState.h"
#include "../../../Engine/SceneManager.h"

GameState::GameState(std::string name, int id, SceneManager* sceneManager)
    : Scene(name, id, sceneManager)
    , m_map(nullptr)
    , m_mapTimer(10.f)
    , m_mapTimerCounter(0.f)
{
}

GameState::~GameState() {}

void GameState::OnCreate()
{
}

void GameState::OnEnter() {
    m_mapTimerCounter = 0.f;

    m_map = new GameMap(m_sceneManager->GetSharedContext());
    m_map->LoadMap("Map1.map");

    EntityManager* eMng = m_sceneManager->GetSharedContext()->m_entityManager;
    eMng->Add(EntityType::Player, "Player");
    eMng->Find("Player")->SetPosition(m_map->GetPlayerStartLocation());

    eMng->Add(EntityType::Enemy, "Enemy");
    eMng->Find("Enemy")->SetPosition(m_map->GetEnemyStartLocs()[0]);
}

void GameState::Update(float deltaTime)
{
    m_mapTimerCounter += deltaTime;

    if (m_mapTimerCounter >= m_mapTimer)
        m_sceneManager->SwitchState("End");

    m_map->Update(deltaTime);
}

void GameState::Render()
{
    m_map->Render();
}

void GameState::OnExit() {
    m_sceneManager->GetSharedContext()->m_entityManager->Purge();
}

void GameState::OnDelete() {
    delete m_map;
    m_map = nullptr;
}
