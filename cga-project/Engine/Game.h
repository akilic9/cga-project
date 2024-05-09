#pragma once
#include "CWindow.h"
#include "SharedContext.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TextureLoader.h"
#include "EntityManager.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Update(float deltaTime);
    void FixedUpdate();
    void LateUpdate();
    void Render();
    void HandleInput();

    CWindow& GetWindow() { return m_window; }

private:
    CWindow m_window;
    SharedContext m_sharedContext;
    SceneManager m_sceneManager;
    TextureLoader m_textureLoader;
    EntityManager m_entityManager;
};

