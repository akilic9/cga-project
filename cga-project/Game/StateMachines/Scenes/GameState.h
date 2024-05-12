#pragma once
#include "../../Engine/Scene.h"
#include "../../Engine/GameMap.h"
#include "../../Engine/EventManager.h"

class GameState : public Scene
{
public:
    GameState(std::string name, int id, SceneManager* sceneManager);
    ~GameState();

    void OnCreate() override;
    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnExit() override;
    void OnDelete() override;

    void OnPlayerScored();

private:
    GameMap* m_map;
    float m_mapTimer;
    int m_score;

    sf::Font m_font;
    sf::Text m_time;
    sf::Text m_scoreText;
};

