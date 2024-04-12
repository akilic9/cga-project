#pragma once
#include <unordered_map>
#include <functional>
#include "StateBase.h"

using StateList = std::unordered_map<int, StateBase*>;

using StateFactory = std::unordered_map<int, std::function<StateBase* (void)>>;

class StateManagerBase
{
public:
	StateManagerBase();
	~StateManagerBase();

	void Update(float deltaTime);
	void Render();

	
	void SwitchState(int &stateId);

private:
	void CreateState(const int& stateId);
	void RemoveState(int& stateId);

	template<class T>
	void RegisterState(std::string stateName) {
		static int stateId = m_states.size() + 1;
		m_factory[stateId] = [this]() -> StateBase*
		{
			return new T(this);
		};
	}

	StateList m_states;
	StateFactory m_factory;
	int m_activeState;
};