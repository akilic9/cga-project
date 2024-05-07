#pragma once
#include "../../Engine/StateBase.h"

class MainMenuState : public StateBase
{
public:
    MainMenuState(std::string name, int id, StateManager* stateManager);
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

