#include "MainMenuState.h"
#include "../../Engine/SceneManager.h"

MainMenuState::MainMenuState(std::string name, int id, SceneManager* sceneManager)
    : Scene(name, id, sceneManager) {}

MainMenuState::~MainMenuState() {}

void MainMenuState::OnCreate()
{
    m_sceneManager->GetSharedContext()->m_inputManager->AddCallback(m_id, "start_key", &MainMenuState::OnStartPressed, this);

    m_font.loadFromFile("Game/Resources/Fonts/Top Secret.ttf"); //Font from https://www.dafont.com/top-secret-kb.font, accessed 12/05/2024, listed as 100% free by the author.

    m_textTitle.setFont(m_font);
    m_textTitle.setString({ "CITY TANKS" });
    m_textTitle.setCharacterSize(100);
    sf::FloatRect textRect1 = m_textTitle.getLocalBounds();
    m_textTitle.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
    m_textTitle.setPosition(800.f, 100.f);

    m_textControls.setFont(m_font);
    m_textControls.setString({ "Controls:" });
    m_textControls.setCharacterSize(75);
    sf::FloatRect textRect2 = m_textControls.getLocalBounds();
    m_textControls.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
    m_textControls.setPosition(800.f, 250.f);

    m_movement.setFont(m_font);
    m_movement.setString({ "WASD / Arrow keys = Movement" });
    m_movement.setCharacterSize(50);
    sf::FloatRect textRect3 = m_movement.getLocalBounds();
    m_movement.setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
    m_movement.setPosition(800, 350.f);

    m_shoot.setFont(m_font);
    m_shoot.setString({ "SAPCE = Shoot" });
    m_shoot.setCharacterSize(50);
    sf::FloatRect textRect5 = m_shoot.getLocalBounds();
    m_shoot.setOrigin(textRect5.left + textRect5.width / 2.0f, textRect5.top + textRect5.height / 2.0f);
    m_shoot.setPosition(800, 450.f);

    m_start.setFont(m_font);
    m_start.setString({ "PRESS B TO START" });
    m_start.setCharacterSize(50);
    sf::FloatRect textRect4 = m_start.getLocalBounds();
    m_start.setOrigin(textRect4.left + textRect4.width / 2.0f, textRect4.top + textRect4.height / 2.0f);
    m_start.setPosition(800.f, 650.f);
}

void MainMenuState::OnEnter() {}

void MainMenuState::Update(float deltaTime)
{
}

void MainMenuState::Render()
{
    sf::RenderWindow* window = m_sceneManager->GetSharedContext()->m_window->GetRenderWindow();
    window->draw(m_textTitle);
    window->draw(m_textControls);
    window->draw(m_movement);
    window->draw(m_shoot);
    window->draw(m_start);
}

void MainMenuState::OnExit() {}

void MainMenuState::OnDelete()
{
    m_sceneManager->GetSharedContext()->m_inputManager->RemoveCallback(m_id, "start_key");
}

void MainMenuState::OnStartPressed(InputBinding* binding)
{
    m_sceneManager->SwitchState("Game");
}
