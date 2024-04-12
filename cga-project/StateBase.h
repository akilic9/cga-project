#pragma once
#include <string>

class StateBase
{
public:
	StateBase() : m_name(""), m_id(-1) {};
	virtual ~StateBase() {};

	virtual void OnEnter() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnExit() = 0;

private:
	std::string m_name;
	int m_id;
};

