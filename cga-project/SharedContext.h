#pragma once
#include "CWindow.h"
#include "InputManager.h"
#include "TextureLoader.h"

struct SharedContext {
	SharedContext()
		: m_window(nullptr)
		, m_inputManager(nullptr)
		, m_textureLoader(nullptr)
	{}

	CWindow * m_window;
	InputManager* m_inputManager;
	TextureLoader* m_textureLoader;
};