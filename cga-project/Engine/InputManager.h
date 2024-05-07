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

//TODO: Only designed for keyboard input and close button as a start, needs to be expanded to work with other types.
//Input type -> key code(if any)
struct InputBinding {
    InputBinding(const std::string& name, std::pair<InputType, int> map) : m_name(name), m_inputMap(map) {}

    std::pair<InputType, int> m_inputMap;
    std::string m_name;
};

//Name -> binding
using InputBindings = std::unordered_map<std::string, std::vector<InputBinding*>>;

//Input name -> target function
using Callback = std::unordered_map<std::string, std::function<void(InputBinding*)>>;

//Scene id -> scene's callbacks
using SceneCallbacks = std::unordered_map<int, Callback>;

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void HandleInputs(sf::Event event);

    bool AddBinding(std::string name, std::pair<InputType, int> map);
    bool RemoveBinding(std::string bindingName);

    //Add a callback - ie register to a keybind trigger event on a scene basis.
    template<class T>
    bool AddCallback(const int sceneId, const std::string& callbackName, void(T::* func)(InputBinding*), T* instance)
    {
        //Create a [sceneId, default constructor callback] element
        auto itr = m_callbacks.emplace(sceneId, Callback()).first;
        //Black magic https://en.cppreference.com/w/cpp/utility/functional/placeholders
        auto temp = std::bind(func, instance, std::placeholders::_1);
        //Store the bound function and callback name into the previously default callback
        return itr->second.emplace(callbackName, temp).second;
    }

    //Remove a callback ie unregister from a keybind on a scene basis.
    void RemoveCallback(int sceneId, const std::string& callbackName);

    /*If not passed a window, this function will return the mouse position relative to desktop origin.
    Window MUST be passed in to get the position within the window.*/
    sf::Vector2i GetMousePos(sf::RenderWindow* window = nullptr) { return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition()); }

    //Set window focus flag.
    void SetHasFocus(bool isFocused) { if (isFocused == m_hasFocus) return; m_hasFocus = isFocused; }
    inline void SetCurrentSceneId(const int& id) { if (m_currentSceneId == id) return; m_currentSceneId = id; }
    
private:
    bool m_hasFocus;
    InputBindings m_inputBindings;
    SceneCallbacks m_callbacks;
    int m_currentSceneId;

    //Load keybinds from cfg file.
    void LoadBindings();
};