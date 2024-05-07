#pragma once
#include "../../Engine/StateBase.h"
#include "../../Engine/GameMap.h"

class GameState : public StateBase
{
public:
    GameState(std::string name, int id, StateManager* stateManager);
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

