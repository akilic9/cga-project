#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

// Wrapper for SFML Window
class CWindow
{
public:
// -------------- Constructor/Destructor --------------
	CWindow();
	CWindow(const std::string& title);
	CWindow(const std::string& title, const sf::Vector2u windowSize);
	~CWindow();
// ----------------------------------------------------

	void Update();
	void BeginDraw() { m_window.clear(sf::Color::Black); }
	void EndDraw() { m_window.display(); }
	void Draw(sf::Drawable& drawable) { m_window.draw(drawable); }

// -------------- Helper Methods ----------------------
	const sf::Vector2u& GetWindowSize() { return m_window.getSize(); }
	const bool& IsOpen() { return m_window.isOpen(); }

private:
// -------------- Private Methods ---------------------
	void CreateWindow(const std::string& title, const sf::Vector2u& windowSize);
	void ToggleFullscreen();

// -------------- Variables ---------------------------
	bool m_isFullscreen;
	const std::string m_title;
	sf::RenderWindow m_window;
};

