#include "CWindow.h"
#include "SFML/Window/Event.hpp"

const sf::Vector2u DEFAULT_WINDOWED_SIZE = sf::Vector2u(1600, 900);
const std::string DEFAULT_TITLE = "SFML Window";
const bool DEFAULT_FULLSCREEN = false;

CWindow::CWindow() :
	m_isFullscreen(DEFAULT_FULLSCREEN),
	m_eventManager(nullptr)
{
	m_eventManager = new EventManager;
	InitWindowEvents();
	CreateWindow(DEFAULT_TITLE, DEFAULT_WINDOWED_SIZE);
}

CWindow::CWindow(const std::string& title) :
	m_isFullscreen(DEFAULT_FULLSCREEN),
	m_eventManager(nullptr)
{
	m_eventManager = new EventManager;
	InitWindowEvents();
	CreateWindow(title, DEFAULT_WINDOWED_SIZE);
}

CWindow::CWindow(const std::string& title, const sf::Vector2u windowSize) :
	m_isFullscreen(DEFAULT_FULLSCREEN),
	m_eventManager(nullptr)
{
	m_eventManager = new EventManager;
	InitWindowEvents();
	CreateWindow(title, windowSize);
}

CWindow::~CWindow()
{
	m_window.close();
}

void CWindow::InitWindowEvents()
{
	m_eventManager->AddCallback("fullscreen_toggle", &CWindow::ToggleFullscreen, this);
	m_eventManager->AddCallback("window_close", &CWindow::CloseWindow, this);
}

void CWindow::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus)
			m_eventManager->SetHasFocus(false);
		else if (event.type == sf::Event::GainedFocus)
			m_eventManager->SetHasFocus(true);

		m_eventManager->HandleEvent(event);
	}
	m_eventManager->Update();
}

void CWindow::CloseWindow(EventDetails* eventDetails)
{
	m_window.close();
}

void CWindow::CreateWindow(const std::string& title, const sf::Vector2u& windowSize)
{
	auto windowStyle = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	m_window.create(sf::VideoMode(windowSize.x, windowSize.y), title, windowStyle);
}

void CWindow::ToggleFullscreen(EventDetails* eventDetails)
{
	auto size = m_window.getSize();
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	// TODO: Adjust size here to fullscreen specific if m_isFullscreen == true.
	CreateWindow(m_title, size);
}