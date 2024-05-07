#include "InputManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

InputManager::InputManager()
    : m_hasFocus(true)
    , m_currentSceneId(-2)
{
    LoadBindings();
}

InputManager::~InputManager() {}

void InputManager::HandleInputs(sf::Event event)
{
    if (!m_hasFocus)
        return;

    for (auto& binding : m_inputBindings) {
        for (auto& b : binding.second) {
            if (b->m_inputMap.first == (InputType)event.type) {
                if (event.type == sf::Event::MouseButtonReleased)
                    return;
                if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                    if (event.type != sf::Event::Closed && b->m_inputMap.second != event.key.code)
                        return;

                    auto sceneItr = m_callbacks.find(m_currentSceneId);
                    if (sceneItr != m_callbacks.end())
                        if (auto key = sceneItr->second.find(binding.first); key != sceneItr->second.end())
                            key->second(b);

                    auto indItr = m_callbacks.find(-1); //-1 is callbacks that are scene independent.
                    if (indItr != m_callbacks.end())
                        if (auto key = indItr->second.find(binding.first); key != indItr->second.end())
                            key->second(b);
                }
            }
        }
    }
}

bool InputManager::AddBinding(std::string name, std::pair<InputType, int> map)
{
    InputBinding *binding = new InputBinding(name, map);
    m_inputBindings[name].push_back(binding);
    return true;
}

bool InputManager::RemoveBinding(std::string bindingName)
{
    if (auto binding = m_inputBindings.find(bindingName); binding == m_inputBindings.end())
        return false;
    else {
        for (auto& b : binding->second) { //Delete the binding pointers in vector.
            delete b;
            b = nullptr;
        }
        binding->second.clear(); //Clear vector.
        m_inputBindings.erase(binding); //Erase map item.
        return true;
    }
}

void InputManager::RemoveCallback(int sceneId, const std::string& callbackName)
{
    //Check if callbacks for this scene exist.
    auto sceneItr = m_callbacks.find(sceneId);
    if (sceneItr == m_callbacks.end())
        return; //If not return.

    //Check if a keybind by this name exist in this scene's callbacks.
    auto keyItr = sceneItr->second.find(callbackName);
    if (keyItr == sceneItr->second.end())
        return; //If not return.

    //Finally delete the binding callback you found.
    sceneItr->second.erase(callbackName);
}

void InputManager::LoadBindings()
{
    std::ifstream bindingsStream;
    std::string filePath = "Game/Data/InputBindings.cfg";
    bindingsStream.open(filePath);

    // Can't open file.
    if (!bindingsStream.is_open())
        return;

    std::string line;
    while (std::getline(bindingsStream, line)) {
        std::string eqSep = "=";

        if (int sepIndex = line.find(eqSep); sepIndex != std::string::npos) {
            std::string actionName = line.substr(0, sepIndex);
            std::string actionCodes = line.substr(sepIndex + eqSep.length(), line.length());

            std::string actionSep = "/";
            int index = actionCodes.find(actionSep);

            while (index != std::string::npos) {
                std::string actionEvent = actionCodes.substr(0, index);
                std::string eventSep = ":";
                
                actionCodes = actionCodes.substr(index + actionSep.length(), actionCodes.length());
                index = actionCodes.find(actionSep);

                if (int i = actionEvent.find(eventSep); i != std::string::npos) {
                    int eventType = stoi(actionEvent.substr(0, i));
                    int eventData = stoi(actionEvent.substr(i + eventSep.length(), actionEvent.length()));

                    AddBinding(actionName, std::make_pair((InputType)eventType, eventData));
                }
            }
        }
    }
    bindingsStream.close();
}
