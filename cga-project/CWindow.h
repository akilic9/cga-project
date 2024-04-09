#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "InputManager.h"

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
	void CloseWindow(InputBinding*);

// -------------- Helper Methods ----------------------
	const sf::Vector2u& GetWindowSize() { return m_window.getSize(); }
	const bool& IsOpen() { return m_window.isOpen(); }
	InputManager* GetInputManager() { return m_inputManager; }

private:
// -------------- Private Methods ---------------------
	void CreateWindow(const std::string& title, const sf::Vector2u& windowSize);
	void ToggleFullscreen(InputBinding*);

// -------------- Variables ---------------------------
	bool m_isFullscreen;
	const std::string m_title;
	sf::RenderWindow m_window;
	InputManager* m_inputManager;

	inline static const sf::Vector2u DEFAULT_WINDOWED_SIZE = sf::Vector2u(1600, 900);
	inline static const std::string DEFAULT_TITLE = "SFML Window";
	inline static const bool DEFAULT_FULLSCREEN = false;
};

