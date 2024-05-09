#pragma once
#include "CWindow.h"
#include "InputManager.h"
#include "TextureLoader.h"
#include "EntityManager.h"

class GameMap;
class SceneManager;

struct SharedContext {
    SharedContext()
        : m_window(nullptr)
        , m_inputManager(nullptr)
        , m_mapManager(nullptr)
        , m_textureLoader(nullptr)
        , m_sceneManager(nullptr) {}

    CWindow * m_window;
    InputManager* m_inputManager;
    TextureLoader* m_textureLoader;
    GameMap* m_mapManager;
    SceneManager* m_sceneManager;
    EntityManager* m_entityManager;
};