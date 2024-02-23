#include "CWindow.h"
#include "SFML/Window/Event.hpp"

const sf::Vector2u DEFAULT_WINDOWED_SIZE = sf::Vector2u(1600, 900);
const char* DEFAULT_TITLE = "SFML Window";
const bool DEFAULT_FULLSCREEN = false;

CWindow::CWindow() :
	m_isFullscreen(DEFAULT_FULLSCREEN)
{
	CreateWindow(DEFAULT_TITLE, DEFAULT_WINDOWED_SIZE);
}

CWindow::CWindow(const char* title) :
	m_isFullscreen(DEFAULT_FULLSCREEN)
{
	CreateWindow(title, DEFAULT_WINDOWED_SIZE);
}

CWindow::CWindow(const char* title, const sf::Vector2u windowSize) :
	m_isFullscreen(DEFAULT_FULLSCREEN)
{
	CreateWindow(title, windowSize);
}

CWindow::~CWindow()
{
	m_window.close();
}

void CWindow::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
		else if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::P)
		{
			ToggleFullscreen();
		}
	}
}

void CWindow::CreateWindow(const char* title, const sf::Vector2u& windowSize)
{
	auto windowStyle = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	m_window.create(sf::VideoMode(windowSize.x, windowSize.y), title, windowStyle);
}

void CWindow::ToggleFullscreen()
{
	auto size = m_window.getSize();
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	// TODO: Adjust size here to fullscreen specific if m_isFullscreen == true.
	CreateWindow(m_title, size);
}