#include "Game.h"

Game::Game() : 
	m_window("CGA Project")
{
	m_context.m_window = &m_window;
	m_context.m_inputManager = &m_window.GetInputManager();
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
}

void Game::FixedUpdate()
{
}

void Game::Render()
{
	m_window.BeginDraw();
	m_window.EndDraw();
}

void Game::HandleInput()
{
}
