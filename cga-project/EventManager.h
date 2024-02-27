#pragma once
#include "SFML/Window/Event.hpp"
#include <variant>
#include <vector>
#include <unordered_map>

class EventManager
{
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
		Mouse,
		Joystick
	};

	struct EventInfo {
		EventInfo() { m_eventCode = 0; }
		EventInfo(int eventCode) { m_eventCode = eventCode; }
		int m_eventCode; //TODO: The book uses union for this, try std::variant when you need more types. Internet says use variant over union unless you need C compatibility.
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
};

