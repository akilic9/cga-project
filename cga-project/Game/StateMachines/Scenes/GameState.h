#pragma once
#include "../../Engine/Scene.h"
#include "../../Engine/GameMap.h"

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

private:
    GameMap* m_map;
    float m_mapTimer;
    float m_mapTimerCounter;
};

