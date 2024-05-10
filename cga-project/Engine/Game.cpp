#include "Game.h"
#include "../Game/StateMachines/Scenes/MainMenuState.h"
#include "../Game/StateMachines/Scenes/GameState.h"

Game::Game()
    : m_window("CGA Project")
    , m_sceneManager(&m_sharedContext)
    , m_textureLoader()
    , m_entityManager(&m_sharedContext)
{
    m_sharedContext.m_window = &m_window;
    m_sharedContext.m_inputManager = &m_window.GetInputManager();
    m_sharedContext.m_textureLoader = &m_textureLoader;
    m_sharedContext.m_entityManager = &m_entityManager;

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
    m_entityManager.Update(deltaTime);
}

void Game::FixedUpdate() {}

void Game::LateUpdate()
{
    m_sceneManager.ProcessRemovals();
    m_entityManager.ProcessRemovals();
}

void Game::Render()
{
    m_window.BeginDraw();
    m_sceneManager.Render();
    m_entityManager.Render();
    m_window.EndDraw();
}

void Game::HandleInput() {}