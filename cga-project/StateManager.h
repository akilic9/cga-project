#pragma once
#include <unordered_map>
#include "StateBase.h"

using StateList = std::unordered_map<int, StateBase*>;

using StateFactory = std::unordered_map<int, StateBase* (void)>;

class StateManagerBase
{
public:
	StateManagerBase();
	~StateManagerBase();

	void Update(float deltaTime);
	void Render();

	
	void SwitchState(int &stateId);

private:
	void CreateState(int &stateId);
	void RemoveState(int& stateId);

	template<class T>
	void RegisterState(std::string stateName) {
		static int stateId = m_states.size()++;
		m_stateFactory[stateId] = [this](stateName, stateId) -> BaseState*
		{
			return new T(this);
		};
	}

	StateList m_states;
	StateFactory m_factory;
	int m_activeState;
};