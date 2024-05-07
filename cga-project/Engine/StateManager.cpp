#include "StateManager.h"

StateManager::StateManager(SharedContext* sharedContext)
    : m_activeState(-1)
    , m_sharedContext(sharedContext) {}

StateManager::~StateManager()
{
    for (auto& itr : m_states) {
        itr.second->OnDelete();
        delete itr.second;
    }
}

/*
Update current state.
*/
void StateManager::Update(float deltaTime)
{
    if (m_states.empty())
        return;

    m_states[m_activeState]->Update(deltaTime);
}

/*
Render current state.
*/
void StateManager::Render()
{
    if (m_states.empty())
        return;

    m_states[m_activeState]->Render();
}

/*
Switch to another state
*/
void StateManager::SwitchState(const int& stateId)
{
    if (auto s = m_states.find(stateId); s != m_states.end()) {
        m_states[m_activeState]->OnExit();
        m_activeState = stateId;
        m_states[m_activeState]->OnEnter();
    }
    else {
        CreateState(stateId);
        m_activeState = stateId;
    }
}

/*
Switch to another state.
*/
void StateManager::SwitchState(const std::string& stateName)
{
    if (auto itr = m_nameToIdMap.find(stateName); itr != m_nameToIdMap.end())
        SwitchState(m_nameToIdMap[stateName]);
}

/*
Queue a state to be removed.
*/
void StateManager::QueueForRemoval(const int& stateId)
{
    m_removalQueue.push_back(stateId);
}

/*
Handle removals.
*/
void StateManager::ProcessRemovals()
{
    while (m_removalQueue.begin() != m_removalQueue.end()) {
        RemoveState(*m_removalQueue.begin());
        m_removalQueue.erase(m_removalQueue.begin());
    }
}

/*
Add a state and add it to the states list.
*/
void StateManager::CreateState(const int& stateId)
{
    if (auto s = m_factory.find(stateId); s != m_factory.end()) {
        StateBase* state = s->second();
        m_states[stateId] = state;
        state->OnCreate();
    }
}

/*
Remove a state from the list.
*/
void StateManager::RemoveState(const int& stateId)
{
    if (auto s = m_states.find(stateId); s != m_states.end()) {
        s->second->OnDelete();
        delete s->second;
        m_states.erase(s->first);
    }
}
