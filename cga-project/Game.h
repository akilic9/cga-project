#pragma once
#include "CWindow.h"
#include "SharedContext.h"
#include "InputManager.h"
#include "StateManager.h"
#include "TextureLoader.h"

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
    StateManager m_gameStateManager;
    TextureLoader m_textureLoader;
};

