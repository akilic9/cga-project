#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class CWindow
{

public:
	// -------------- Constructor/Destructor --------------
	CWindow();
	CWindow(const char* title, const sf::Vector2u windowSize = sf::Vector2u(1600, 900));
	~CWindow();

	// -------------- Public Methods --------------
	void Update();
	void BeginDraw() { m_window.clear(sf::Color::Black); }
	void EndDraw() { m_window.display(); }
	void Draw(sf::Drawable& drawable) { m_window.draw(drawable); }

	// -------------- Getter Methods --------------
	const sf::Vector2u& GetWindowSize() { return m_window.getSize(); }

private:
	// -------------- Private Methods --------------
	void CreateWindow(const char* title, const sf::Vector2u& windowSize);
	void ToggleFullscreen();
	void Destroy();

	// -------------- Variables --------------
	bool m_isFullscreen;
	const char* m_title;
	sf::RenderWindow m_window;
};

