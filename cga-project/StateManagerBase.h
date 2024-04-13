#pragma once
#include <unordered_map>
#include <functional>
#include "StateBase.h"
#include "SharedContext.h"

using StateList = std::unordered_map<int, StateBase*>;

using NameToId = std::unordered_map<std::string, int>;

using StateFactory = std::unordered_map<int, std::function<StateBase* (void)>>;

class StateManagerBase
{
public:
	StateManagerBase(SharedContext* sc);
	~StateManagerBase();

	void Update(float deltaTime);
	void Render();

	
	void SwitchState(int stateId);
	void SwitchState(std::string stateName);

private:
	void CreateState(const int& stateId);
	void RemoveState(int& stateId);

	template<class T>
	void RegisterState(std::string stateName) {
		static int stateId = m_states.size() + 1;
		m_factory[stateId] = [stateName, stateId, this]() -> StateBase*
		{
			return new T(stateName, stateId, this);
		};
	}

	StateList m_states;
	StateFactory m_factory;
	NameToId m_nameToIdMap;
	int m_activeState;
	SharedContext* m_sc;
};