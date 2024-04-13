#pragma once
#include "CWindow.h"
#include "SharedContext.h"
#include "InputManager.h"

//Aybike: Doesn't makes sense to me that game owns the window, but seems like the structure will change in the later chapters of the book. Just rolling with it atm.
class Game
{
public:
// -------------- Constructor/Destructor --------------
	Game();
	~Game();
// ----------------------------------------------------

	void Init();
	void Update(float deltaTime);
	void FixedUpdate();
	void Render();
	void HandleInput();

// -------------- Helper Methods --------------
	CWindow& GetWindow() { return m_window; }

private:
	CWindow m_window;
	SharedContext m_context;
};

