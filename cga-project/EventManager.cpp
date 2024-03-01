#include "EventManager.h"
#include "LoggerUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>

EventManager::EventManager() :
	m_hasFocus(true)
{
	LoadBindings();
}

EventManager::~EventManager()
{
	for (auto &binding : m_eventBindings) {
		delete binding.second;
		binding.second = nullptr;
	}
}

bool EventManager::AddBinding(EventBinding* eventBinding)
{
	if (m_eventBindings.find(eventBinding->m_name) != m_eventBindings.end())
		return false;

	m_eventBindings[eventBinding->m_name] = eventBinding;
	return true;
}

void EventManager::RemoveBinding(std::string bindingName)
{
	if (auto binding = m_eventBindings.find(bindingName); binding != m_eventBindings.end()) {
		delete binding->second;
		binding->second = nullptr;
		m_eventBindings.erase(binding);
	}
}

void EventManager::SetHasFocus(const bool& isFocused)
{
	if (isFocused == m_hasFocus)
		return;

	m_hasFocus = isFocused;
}

void EventManager::HandleEvent(sf::Event& newEvent)
{

}

void EventManager::Update()
{
	if (!m_hasFocus)
		return;
}

void EventManager::LoadBindings()
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
