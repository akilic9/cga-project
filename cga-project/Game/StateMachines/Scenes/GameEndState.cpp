#include "GameEndState.h"
#include "../../Engine/SceneManager.h"

GameEndState::GameEndState(std::string name, int id, SceneManager* sceneManager)
    : Scene(name, id, sceneManager) {}

GameEndState::~GameEndState()
{
}

void GameEndState::OnCreate()
{
    m_sceneManager->GetSharedContext()->m_inputManager->AddCallback(m_id, "restart_key", &GameEndState::OnRestartPressed, this);

    m_font.loadFromFile("Game/Resources/Fonts/Top Secret.ttf"); //Font from https://www.dafont.com/top-secret-kb.font, accessed 12/05/2024, listed as 100% free by the author.

    m_textTitle.setFont(m_font);
    m_textTitle.setString({ "GAME OVER" });
    m_textTitle.setCharacterSize(100);
    sf::FloatRect textRect1 = m_textTitle.getLocalBounds();
    m_textTitle.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
    m_textTitle.setPosition(800.f, 100.f);

    m_textReturn.setFont(m_font);
    m_textReturn.setString({ "PRESS R FOR MAIN MENU" });
    m_textReturn.setCharacterSize(50);
    sf::FloatRect textRect2 = m_textReturn.getLocalBounds();
    m_textReturn.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
    m_textReturn.setPosition(800.f, 550.f);
}

void GameEndState::OnEnter()
{
}

void GameEndState::Update(float deltaTime)
{
}

void GameEndState::Render()
{
    sf::RenderWindow* window = m_sceneManager->GetSharedContext()->m_window->GetRenderWindow();
    window->draw(m_textTitle);
    window->draw(m_textReturn);
}

void GameEndState::OnExit()
{
}

void GameEndState::OnDelete()
{
}

void GameEndState::OnRestartPressed(InputBinding* binding)
{
    m_sceneManager->SwitchState("MainMenu");
}
