#include "GameState.h"
#include "../../../Engine/SceneManager.h"

GameState::GameState(std::string name, int id, SceneManager* sceneManager)
    : Scene(name, id, sceneManager)
{
    m_map = new GameMap(m_sceneManager->GetSharedContext());
    m_map->LoadMap("Map1.map");

    EntityManager* eMng = m_sceneManager->GetSharedContext()->m_entityManager;
    eMng->Add(EntityType::Player, "Player");
    eMng->Find("Player")->SetPosition(m_map->GetPlayerStartLocation());

    eMng->Add(EntityType::Enemy, "Enemy");
    eMng->Find("Enemy")->SetPosition(m_map->GetEnemyStartLocs()[0]);

    if (auto enemy = eMng->Find("Enemy")) {
        auto e = static_cast<Enemy*>(enemy);
        e->SetBasePos(m_map->GetBaseLocation());
    }
}

GameState::~GameState() {}

void GameState::OnCreate()
{
    //m_font.loadFromFile("Resources/Jersey10-Regular.ttf");
    //m_text.setFont(m_font);
    //m_text.setString({ "game state" });
    //m_text.setCharacterSize(15);
    //sf::FloatRect textRect = m_text.getLocalBounds();
    //m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    //m_text.setPosition(100.f, 100.f);
}

void GameState::OnEnter() {}

void GameState::Update(float deltaTime)
{
    m_map->Update(deltaTime);

    EntityManager* eMng = m_sceneManager->GetSharedContext()->m_entityManager;
    if (auto enemy = eMng->Find("Enemy"); auto player = eMng->Find("Player"))
        static_cast<Enemy*>(enemy)->SetPlayerPos(player->GetPosition());
}

void GameState::Render()
{
    m_map->Render();
}

void GameState::OnExit() {}

void GameState::OnDelete() {
    delete m_map;
    m_map = nullptr;
}
