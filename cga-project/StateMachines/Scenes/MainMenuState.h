#pragma once
#include "../../StateBase.h"
#include "SFML/Graphics/Text.hpp"

class MainMenuState : public StateBase
{
public:
	MainMenuState(std::string name, int id, StateManagerBase* stateManager);
	~MainMenuState();

	void OnCreate();
	void OnEnter();
	void Update(float deltaTime);
	void Render();
	void OnExit();
	void OnDelete();

private:
	sf::Text m_text;
	float m_switchTime;
	float m_switchCounter;
};

