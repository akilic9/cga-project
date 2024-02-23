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

void Game::Update()
{
	m_window.Update();
}

void Game::Render()
{
	m_window.BeginDraw();
	m_window.EndDraw();
}

void Game::HandleInput()
{
}
