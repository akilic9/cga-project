#pragma once
#include <string>

class StateBase
{
public:
	StateBase(std::string name, int id) : m_name(name), m_id(id) {};
	virtual ~StateBase() {};

	virtual void OnCreate() = 0;
	virtual void OnEnter() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void OnExit() = 0;
	virtual void OnDelete() = 0;

private:
	std::string m_name;
	int m_id;
};

