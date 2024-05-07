#include "SceneManager.h"

SceneManager::SceneManager(SharedContext* sharedContext)
    : m_sharedContext(sharedContext)
{
}

SceneManager::~SceneManager() {}

void SceneManager::SwitchState(const int& stateId)
{
    StateManager::SwitchState(stateId);
    m_sharedContext->m_inputManager->SetCurrentSceneId(stateId);
}

void SceneManager::SwitchState(const std::string& stateName)
{
    if (auto itr = m_nameToIdMap.find(stateName); itr != m_nameToIdMap.end())
        SwitchState(m_nameToIdMap[stateName]);
}
