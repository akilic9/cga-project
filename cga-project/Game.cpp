#include "Game.h"

Game::Game() : 
	m_window("CGA Project")
{
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
