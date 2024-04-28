#pragma once
#include <unordered_map>
#include <functional>
#include "StateBase.h"
#include "SharedContext.h"

using StateList = std::unordered_map<int, StateBase*>;

using NameToId = std::unordered_map<std::string, int>;

using StateFactory = std::unordered_map<int, std::function<StateBase* (void)>>;

class StateManager
{
public:
    StateManager(SharedContext* sc);
    ~StateManager();

    void Update(float deltaTime);
    void Render();

    /*Register a state to create the state object.*/
    template<class T>
    void RegisterState(const std::string& stateName) {
        int stateId = m_stateCount++;
        m_nameToIdMap[stateName] = stateId;
        m_factory[stateId] = [stateName, stateId, this]() -> StateBase*
            {
                return new T(stateName, stateId, this);
            };
    }
    
    void SwitchState(const int& stateId);
    void SwitchState(const std::string& stateName);

    void QueueForRemoval(const int& stateId);
    void ProcessRemovals();

    SharedContext* GetSharedContext() { return m_sc; };

private:
    StateList m_states;
    StateFactory m_factory;
    NameToId m_nameToIdMap;
    int m_activeState;
    SharedContext* m_sc;
    int m_stateCount = 0;
    std::vector<int> m_removalQueue;

    void CreateState(const int& stateId);
    void RemoveState(const int& stateId);
};