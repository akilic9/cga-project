#include "GameState.h"
#include "../../Engine/SceneManager.h"
#include "../../PowerUpNuke.h"

GameState::GameState(std::string name, int id, SceneManager* sceneManager)
    : Scene(name, id, sceneManager)
    , m_map(nullptr)
    , m_mapTimer(10.f)
    , m_score(0)
{
}

GameState::~GameState() {}

void GameState::OnCreate()
{
    m_font.loadFromFile("Game/Resources/Fonts/Top Secret.ttf"); //Font from https://www.dafont.com/top-secret-kb.font, accessed 12/05/2024, listed as 100% free by the author.
    m_time.setFont(m_font);
    m_time.setPosition(800.f, 30.f);
    m_time.setFillColor(sf::Color::Black);
    m_time.setCharacterSize(50);

    m_scoreText.setFont(m_font);
    m_scoreText.setFillColor(sf::Color::Black);
    m_scoreText.setCharacterSize(50);
}

void GameState::OnEnter() {
    m_mapTimer = 10.f;

    m_map = new GameMap(m_sceneManager->GetSharedContext());
    m_map->LoadMap("Map1.map");

    EntityManager* eMng = m_sceneManager->GetSharedContext()->m_entityManager;
    eMng->Add(EntityType::Player, "Player");
    eMng->Find("Player")->SetPosition(m_map->GetPlayerStartLocation());

    eMng->Add(EntityType::Enemy, "Enemy");
    eMng->Find("Enemy")->SetPosition(m_map->GetEnemyStartLocs()[0]);
    static_cast<Enemy*>(eMng->Find("Enemy"))->SetSpawnLoc(m_map->GetEnemyStartLocs()[0]);
    static_cast<Enemy*>(eMng->Find("Enemy"))->m_OnDeath.Subscribe(this, &GameState::OnPlayerScored);

    eMng->Add(EntityType::PowerUp, "PowerUp");
    static_cast<PowerUpNuke*>(eMng->Find("PowerUp"))->m_OnCollected.Subscribe(this, &GameState::OnNuked);
}

void GameState::Update(float deltaTime)
{
    m_mapTimer -= deltaTime;

    if (m_mapTimer < 0.f)
        m_sceneManager->SwitchState("End");

    m_map->Update(deltaTime);
}

void GameState::Render()
{
    m_map->Render();
    sf::RenderWindow* window = m_sceneManager->GetSharedContext()->m_window->GetRenderWindow();
    m_time.setString({ "TIME LEFT: " + std::to_string((int)m_mapTimer) });
    sf::FloatRect textRect1 = m_time.getLocalBounds();
    m_time.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
    window->draw(m_time);

    m_scoreText.setString({ "SCORE: " + std::to_string(m_score) });
    sf::FloatRect textRect2 = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
    m_scoreText.setPosition(textRect2.width / 2.0f, 30.f);
    window->draw(m_scoreText);
}

void GameState::OnExit() {
    m_sceneManager->GetSharedContext()->m_entityManager->Purge();
}

void GameState::OnDelete() {
    delete m_map;
    m_map = nullptr;
}

void GameState::OnPlayerScored()
{
    m_score += 100;
}

void GameState::OnNuked()
{
    EntityManager* eMng = m_sceneManager->GetSharedContext()->m_entityManager;
    static_cast<Enemy*>(eMng->Find("Enemy"))->Die();
    unsigned int id = eMng->Find("PowerUp")->GetID();
    eMng->QueueForRemoval(id);
}
