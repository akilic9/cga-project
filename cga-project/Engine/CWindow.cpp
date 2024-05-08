#include "CWindow.h"
#include "SFML/Window/Event.hpp"

CWindow::CWindow() :
    m_isFullscreen(DEFAULT_FULLSCREEN)
{
    InitWindowEvents();
    CreateWindow(DEFAULT_TITLE, DEFAULT_WINDOWED_SIZE);
}

CWindow::CWindow(const std::string& title) :
    m_isFullscreen(DEFAULT_FULLSCREEN)
{
    InitWindowEvents();
    CreateWindow(title, DEFAULT_WINDOWED_SIZE);
}

CWindow::CWindow(const std::string& title, const sf::Vector2u windowSize) :
    m_isFullscreen(DEFAULT_FULLSCREEN)
{
    InitWindowEvents();
    CreateWindow(title, windowSize);
}

CWindow::~CWindow()
{
    m_window.close();
}

void CWindow::InitWindowEvents()
{
    m_inputManager.AddCallback(-1, "fullscreen_toggle", &CWindow::ToggleFullscreen, this);
    m_inputManager.AddCallback(-1, "window_close", &CWindow::CloseWindow, this);
}

void CWindow::Update()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::LostFocus)
            m_inputManager.SetHasFocus(false);
        else if (event.type == sf::Event::GainedFocus)
            m_inputManager.SetHasFocus(true);

        m_inputManager.HandleInputs(event);
    }

    m_inputManager.Update();
}

void CWindow::CloseWindow(InputBinding* binding)
{
    m_window.close();
}

void CWindow::CreateWindow(const std::string& title, const sf::Vector2u& windowSize)
{
    auto windowStyle = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;

    m_window.create(sf::VideoMode(windowSize.x, windowSize.y), title, windowStyle);
}

void CWindow::ToggleFullscreen(InputBinding* binding)
{
    auto size = m_window.getSize();
    m_isFullscreen = !m_isFullscreen;
    m_window.close();
    // TODO: Adjust size here to fullscreen specific if m_isFullscreen == true.
    CreateWindow(m_title, size);
}