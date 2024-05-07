#include "Game.h"
#include "../Game/StateMachines/Scenes/MainMenuState.h"
#include "../Game/StateMachines/Scenes/GameState.h"

Game::Game()
    : m_window("CGA Project")
    , m_sceneManager(&m_sharedContext)
    , m_textureLoader()
{
    m_sharedContext.m_window = &m_window;
    m_sharedContext.m_inputManager = &m_window.GetInputManager();
    m_sharedContext.m_textureLoader = &m_textureLoader;

    //Register and set the scenes.
    m_sceneManager.RegisterState<GameState>("Game");
    m_sceneManager.SwitchState("Game");
}

Game::~Game() {}

void Game::Init() {}

void Game::Update(float deltaTime)
{
    m_window.Update();
    m_sceneManager.Update(deltaTime);
}

void Game::FixedUpdate() {}

void Game::LateUpdate()
{
    m_sceneManager.ProcessRemovals();
}

void Game::Render()
{
    m_window.BeginDraw();
    m_sceneManager.Render();
    m_window.EndDraw();
}

void Game::HandleInput() {}
