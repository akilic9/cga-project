#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "EventManager.h"

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

	void InitWindowEvents();
	void Update();
	void BeginDraw() { m_window.clear(sf::Color::Black); }
	void EndDraw() { m_window.display(); }
	void Draw(sf::Drawable& drawable) { m_window.draw(drawable); }
	void CloseWindow(EventDetails* eventDetails);

// -------------- Helper Methods ----------------------
	const sf::Vector2u& GetWindowSize() { return m_window.getSize(); }
	const bool& IsOpen() { return m_window.isOpen(); }
	EventManager* GetEventManager() { return m_eventManager; }

private:
// -------------- Private Methods ---------------------
	void CreateWindow(const std::string& title, const sf::Vector2u& windowSize);
	void ToggleFullscreen(EventDetails* eventDetails);

// -------------- Variables ---------------------------
	bool m_isFullscreen;
	const std::string m_title;
	sf::RenderWindow m_window;
	EventManager* m_eventManager;
};

