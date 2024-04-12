#include "StateManager.h"

StateManagerBase::StateManagerBase() : m_activeState(-1)
{
}

StateManagerBase::~StateManagerBase()
{
	for (auto& itr : m_states) {
		itr.second->OnDelete();
		delete itr.second;
	}
}

void StateManagerBase::Update(float deltaTime)
{
	if (m_states.empty())
		return;

	m_states[m_activeState]->Update(deltaTime);
}

void StateManagerBase::Render()
{
	if (m_states.empty())
		return;

	m_states[m_activeState]->Render();
}

void StateManagerBase::SwitchState(int& stateId)
{
	m_states[m_activeState]->OnExit();
	m_activeState = stateId;
	m_states[m_activeState]->OnEnter();
}

void StateManagerBase::CreateState(int& stateId)
{
	if (auto s = m_factory.find(stateId); s != m_factory.end()) {
		StateBase* state = s->second();
		m_states[stateId] = state;
		state->OnCreate();
	}
}

void StateManagerBase::RemoveState(int& stateId)
{
	if (auto s = m_factory.find(stateId); s != m_factory.end()) {
		s->second()->OnDelete();
		delete s->second();
		m_states.erase(s->first);
	}
}
