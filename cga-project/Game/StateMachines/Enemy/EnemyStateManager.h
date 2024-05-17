#pragma once
#include "../../../Engine/StateManager.h"
#include "EnemyStateBase.h"

class Enemy;

class EnemyStateManager : public StateManager
{
public:
    EnemyStateManager(Enemy* parent);
    ~EnemyStateManager();

    /*Register a state to create the state object.*/
    template<class T>
    void RegisterState(const std::string& stateName) {
        int stateId = m_stateCount++;
        m_nameToIdMap[stateName] = stateId;
        m_factory[stateId] = [stateName, stateId, this]() -> EnemyStateBase*
            { return new T(stateName, stateId, this, m_parent); };
    }

private:
    Enemy* m_parent;
};

