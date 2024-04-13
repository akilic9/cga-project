#include "Game.h"
#include "StateMachines/Scenes/MainMenuState.h"
#include "StateMachines/Scenes/GameState.h"

Game::Game()
	: m_window("CGA Project")
	, m_gameStateManager(&m_sharedContext)
{
	m_sharedContext.m_window = &m_window;
	m_sharedContext.m_inputManager = &m_window.GetInputManager();

	m_gameStateManager.RegisterState<MainMenuState>("MainMenu");
	m_gameStateManager.RegisterState<GameState>("Game");
	m_gameStateManager.SwitchState("MainMenu");
}

Game::~Game()
{
}

void Game::Init()
{
}

void Game::Update(float deltaTime)
{
	m_window.Update();
	m_gameStateManager.Update(deltaTime);
}

void Game::FixedUpdate()
{
}

void Game::LateUpdate()
{
	m_gameStateManager.ProcessRemovals();
}

void Game::Render()
{
	m_window.BeginDraw();
	m_gameStateManager.Render();
	m_window.EndDraw();
}

void Game::HandleInput()
{
}
