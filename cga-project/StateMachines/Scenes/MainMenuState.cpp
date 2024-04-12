#include "MainMenuState.h"
#include "../../StateManagerBase.h"

MainMenuState::MainMenuState(std::string name, int id, StateManagerBase* stateManager)
	: StateBase(name, id, stateManager)
	, m_switchTime(5.0f)
	, m_switchCounter(0.f)
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::OnCreate()
{
	m_text.setString({ "Press SPACE to continue" });
	m_text.setCharacterSize(15);
	m_text.setPosition(100.f, 100.f);
}

void MainMenuState::OnEnter()
{
}

void MainMenuState::Update(float deltaTime)
{
	m_switchCounter += deltaTime;

	if (m_switchCounter > m_switchTime)
	{
		m_switchCounter = 0.f;
		m_stateManager->SwitchState(1);
	}
}

void MainMenuState::Render()
{
}

void MainMenuState::OnExit()
{
}

void MainMenuState::OnDelete()
{
}
