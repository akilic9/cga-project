#pragma once
#include "../../Engine/Scene.h"
#include "../../Engine/GameMap.h"

class GameState : public Scene
{
public:
    GameState(std::string name, int id, SceneManager* sceneManager);
    ~GameState();

    void OnCreate();
    void OnEnter();
    void Update(float deltaTime);
    void Render();
    void OnExit();
    void OnDelete();

private:
    GameMap* m_map;
};

