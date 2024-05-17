#pragma once
#include "../../../Engine/Scene.h"
#include "../../../Engine/InputManager.h"

class GameEndState : public Scene
{
public:    
    GameEndState(std::string name, int id, SceneManager* sceneManager);
    ~GameEndState();

    void OnCreate() override;
    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnExit() override;
    void OnDelete() override;

    void OnRestartPressed(InputBinding* binding);
private:
    sf::Font m_font;

    sf::Text m_textTitle;
    sf::Text m_textReturn;
};

