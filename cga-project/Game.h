#pragma once
#include "CWindow.h"

class Game
{
public:
	// -------------- Constructor/Destructor --------------
	Game();
	~Game();

	// -------------- Public Methods --------------
	void Init();
	void Update(float deltaTime);
	void FixedUpdate();
	void Render();
	void HandleInput();


	// -------------- Helper Methods --------------
	CWindow& GetWindow() { return m_window; }

private:
	CWindow m_window;
};

