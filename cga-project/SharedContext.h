#pragma once
#include "CWindow.h"
#include "InputManager.h"
#include "TextureLoader.h"

class GameMap;

struct SharedContext {
    SharedContext()
        : m_window(nullptr)
        , m_inputManager(nullptr)
        , m_textureLoader(nullptr)
    {}

    CWindow * m_window;
    InputManager* m_inputManager;
    TextureLoader* m_textureLoader;
    GameMap* m_mapManager;
};