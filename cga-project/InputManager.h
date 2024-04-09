#pragma once
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <vector>
#include <unordered_map>
#include <functional>

enum class InputType {
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

//TODO: Only designed for keyboard input as a start, needs to be expanded to work with other types above. Also expand so that multiple bindings can be stored under one name.
//Input type -> key code(if any)
struct InputBinding {
	InputBinding(const std::string& name, std::pair<InputType, int> map) : m_name(name), m_inputMap(map) {}

	std::pair<InputType, int> m_inputMap;
	std::string m_name;
};

//Name -> binding
using InputBindings = std::unordered_map<std::string, InputBinding*>;

//Input name -> target function
using Callbacks = std::unordered_map<std::string, std::function<void(InputBinding*)>>;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void HandleInputs(sf::Event event);

	bool AddBinding(std::string name, std::pair<InputType, int> map);
	bool RemoveBinding(std::string bindingName);

	template<class T>
	bool AddCallback(const std::string& callbackName, void(T::* func)(InputBinding*), T* instance)
	{
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return m_callbacks.emplace(callbackName, temp).second;
	}

	void RemoveCallback(const std::string& callbackName) { m_callbacks.erase(callbackName); }

	/*If not passed a window, this function will return the mouse position relative to desktop origin.
	Window MUST be passed in to get the position within the window.*/
	sf::Vector2i GetMousePos(sf::RenderWindow* window = nullptr) { return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition()); }

	void SetHasFocus(bool isFocused) { if (isFocused == m_hasFocus) return; m_hasFocus = isFocused; }
	
private:
	void LoadBindings();

	bool m_hasFocus;
	InputBindings m_inputBindings;
	Callbacks m_callbacks;
};