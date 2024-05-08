#pragma once
#include "../../Engine/Scene.h"

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

private:
    sf::Text m_text;
    sf::Font m_font;
    float m_switchTime;
    float m_switchCounter;
};

