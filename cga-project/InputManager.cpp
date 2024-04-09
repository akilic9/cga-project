#include "InputManager.h"
#include "LoggerUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>

InputManager::InputManager() :
	m_hasFocus(true)
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
			if (auto itr = m_callbacks.find(b.first); itr != m_callbacks.end())
				(*itr).second(b.second);
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

void InputManager::LoadBindings()
{
	std::ifstream bindingsStream;
	std::string filePath = "Data/InputBindings.cfg";
	bindingsStream.open(filePath);

	// Can't open file.
	if (!bindingsStream.is_open()) {
		CE_OUTPUT_ERROR("Could not read the input bindings file!");
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
				else
					CE_OUTPUT_ERROR("Faulty expression in input bindings!");
			}
		}
		else
			CE_OUTPUT_ERROR("Faulty expression in input bindings!");
	}
	bindingsStream.close();
}
