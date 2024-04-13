#pragma once
#include "CWindow.h"
#include "InputManager.h"

struct SharedContext {
	SharedContext() : m_window(nullptr), m_inputManager(nullptr) {}

	CWindow * m_window;
	InputManager* m_inputManager;
};