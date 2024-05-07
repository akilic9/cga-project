#pragma once
#include "StateManager.h"
#include "SharedContext.h"
class SceneManager : public StateManager
{
public:
    SceneManager(SharedContext* sharedContext);
    ~SceneManager();

    /*Register a state to create the state object.*/
    template<class T>
    void RegisterState(const std::string& stateName) {
        int stateId = m_stateCount++;
        m_nameToIdMap[stateName] = stateId;
        m_factory[stateId] = [stateName, stateId, this]() -> StateBase*
            { return new T(stateName, stateId, this); };
    }

    void SwitchState(const int& stateId) override;
    void SwitchState(const std::string& stateName) override;

    inline SharedContext* GetSharedContext() { return m_sharedContext; }

private:
    SharedContext* m_sharedContext;
};

