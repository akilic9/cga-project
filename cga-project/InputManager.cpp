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

InputManager::~InputManager()
{
}

void InputManager::HandleInputs(sf::Event event)
{
    if (!m_hasFocus)
        return;

    for (auto& b : m_inputBindings) {
        if (b.second->m_inputMap.first == (InputType)event.type && b.second->m_inputMap.second == event.key.code) {
            auto sceneItr = m_callbacks.find(m_currentSceneId);
            if (sceneItr != m_callbacks.end())
                if (auto key = sceneItr->second.find(b.first); key != sceneItr->second.end())
                    key->second(b.second);

            auto indItr = m_callbacks.find(-1); //-1 is callbacks that are scene independent.
            if (indItr != m_callbacks.end())
                if (auto key = indItr->second.find(b.first); key != indItr->second.end())
                    key->second(b.second);

        }
    }
}

bool InputManager::AddBinding(std::string name, std::pair<InputType, int> map)
{
    if (m_inputBindings.find(name) != m_inputBindings.end())
        return false;
    else {
        InputBinding *binding = new InputBinding(name, map);
        m_inputBindings[name] = binding;
        return true;
    }
}

bool InputManager::RemoveBinding(std::string bindingName)
{
    if (auto binding = m_inputBindings.find(bindingName); binding == m_inputBindings.end()) {
        return false;
    }
    else {
        delete binding->second;
        binding->second = nullptr;
        m_inputBindings.erase(binding);
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
    std::string filePath = "Data/InputBindings.cfg";
    bindingsStream.open(filePath);

    // Can't open file.
    if (!bindingsStream.is_open()) {
        return;
    }

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
