#include "MainMenuState.h"
#include "../../Engine/StateManager.h"

MainMenuState::MainMenuState(std::string name, int id, StateManager* stateManager)
    : StateBase(name, id, stateManager)
    , m_switchTime(5.0f)
    , m_switchCounter(0.f) {}

MainMenuState::~MainMenuState() {}

void MainMenuState::OnCreate()
{
    m_font.loadFromFile("Resources/Jersey10-Regular.ttf");
    m_text.setFont(m_font);
    m_text.setString({ "main menu" });
    m_text.setCharacterSize(15);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_text.setPosition(100.f, 100.f);
}

void MainMenuState::OnEnter() {}

void MainMenuState::Update(float deltaTime)
{
    m_switchCounter += deltaTime;

    if (m_switchCounter > m_switchTime)
    {
        m_switchCounter = 0.f;
        m_stateManager->SwitchState(1);
    }
}

void MainMenuState::Render()
{
    sf::RenderWindow* window = m_stateManager->GetSharedContext()->m_window->GetRenderWindow();
    window->draw(m_text);
}

void MainMenuState::OnExit() {}

void MainMenuState::OnDelete() {}
