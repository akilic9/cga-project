#pragma once
#include "../../StateBase.h"

class GameState : public StateBase
{
public:
	GameState(std::string name, int id, StateManagerBase* stateManager);
	~GameState();

	void OnCreate();
	void OnEnter();
	void Update(float deltaTime);
	void Render();
	void OnExit();
	void OnDelete();

private:
	sf::Text m_text;
	sf::Font m_font;
	float m_switchTime;
	float m_switchCounter;
};
