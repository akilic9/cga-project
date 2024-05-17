#pragma once
#include "../../../Engine/Scene.h"
#include "../../../Engine/InputManager.h"

class MainMenuState : public Scene
{
public:
    MainMenuState(std::string name, int id, SceneManager* sceneManager);
    ~MainMenuState();

    void OnCreate() override;
    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnExit() override;
    void OnDelete() override;

    void OnStartPressed(InputBinding* binding);

private:
    sf::Text m_textTitle;
    sf::Text m_textControls;
    sf::Text m_movement;
    sf::Text m_shoot;
    sf::Text m_start;
    sf::Font m_font;
};

