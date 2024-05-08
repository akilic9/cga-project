#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "InputManager.h"

// Wrapper for SFML Window
class CWindow
{
public:
    CWindow();
    CWindow(const std::string& title);
    CWindow(const std::string& title, const sf::Vector2u windowSize);
    ~CWindow();

    void InitWindowEvents();
    void Update();
    void BeginDraw() { m_window.clear(sf::Color::Black); }
    void EndDraw() { m_window.display(); }
    void Draw(sf::Drawable& drawable) { m_window.draw(drawable); }
    void CloseWindow(InputBinding* binding);

    const sf::Vector2u GetWindowSize() const { return m_window.getSize(); }
    const bool IsOpen() const { return m_window.isOpen(); }
    InputManager& GetInputManager() { return m_inputManager; }
    inline sf::RenderWindow* GetRenderWindow() { return &m_window; }

private:
    bool m_isFullscreen;
    const std::string m_title;
    sf::RenderWindow m_window;
    InputManager m_inputManager;

    inline static const sf::Vector2u DEFAULT_WINDOWED_SIZE = sf::Vector2u(1600, 900);
    inline static const std::string DEFAULT_TITLE = "SFML Window";
    inline static const bool DEFAULT_FULLSCREEN = false;

    void CreateWindow(const std::string& title, const sf::Vector2u& windowSize);
    void ToggleFullscreen(InputBinding* binding);
};

