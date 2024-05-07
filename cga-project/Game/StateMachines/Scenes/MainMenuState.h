#pragma once
#include "../../Engine/Scene.h"

class MainMenuState : public Scene
{
public:
    MainMenuState(std::string name, int id, SceneManager* sceneManager);
    ~MainMenuState();

    void OnCreate();
    void OnEnter();
    void Update(float deltaTime);
    void Render();
    void OnExit();
    void OnDelete();

private:
    sf::Text m_text;
    sf::Font m_font;
    float m_switchTime;
    float m_switchCounter;
};

