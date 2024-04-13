#pragma once
#include <string>

class StateManagerBase;

class StateBase
{
public:
	StateBase(std::string name, int id, StateManagerBase* stateManager) : m_name(name), m_id(id), m_stateManager(stateManager) {};
	virtual ~StateBase() {};

	virtual void OnCreate() = 0;
	virtual void OnEnter() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void OnExit() = 0;
	virtual void OnDelete() = 0;

	const std::string& GetName() const { return m_name; }

protected:
	const std::string m_name;
	int m_id;
	StateManagerBase* m_stateManager;
};