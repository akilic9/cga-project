#pragma once
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <variant>
#include <vector>
#include <unordered_map>
#include <functional>

//Aybike: This class is complicated, return here and figure out what's going on in depth.

enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1,
	Mouse
};

struct EventInfo {
	EventInfo() { m_eventCode = 0; }
	EventInfo(int eventCode) { m_eventCode = eventCode; }
	int m_eventCode; //Aybike: The book uses union for this, try std::variant when you need more types. Internet says use variant over union unless you need C compatibility.
};

using EventTypeInfo = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
	EventDetails(const std::string& name) : m_name(name) { Clear(); }
	std::string m_name;
	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode;

	void Clear() {
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

struct EventBinding {
	EventBinding(const std::string& name) : m_name(name), m_count(0), m_details(name) {}

	void BindEvent(EventType type, EventInfo info = EventInfo()) { m_events.emplace_back(type, info); }

	EventTypeInfo m_events;
	std::string m_name;
	int m_count;
	EventDetails m_details;
};

using EventBindings = std::unordered_map<std::string, EventBinding*>;

using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool AddBinding(EventBinding* eventBinding);
	void RemoveBinding(std::string bindingName);

	void SetHasFocus(const bool& isFocused);

	void HandleEvent(sf::Event& newEvent);

	void Update();

	template<class T>
	bool AddCallback(const std::string& callbackName, void(T::* func)(EventDetails*), T* instance)
	{
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return m_callbacks.emplace(callbackName, temp).second;
	}

	void RemoveCallback(const std::string& callbackName) { m_callbacks.erase(callbackName); }

	/*If not passed a window, this function will return the mouse position relative to desktop origin.
	Window MUST be passed in to get the position within the window.*/
	sf::Vector2i GetMousePos(sf::RenderWindow* window = nullptr) { return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition()); }

private:
	void LoadBindings();
	EventBindings m_eventBindings;
	Callbacks m_callbacks;
	bool m_hasFocus;
};