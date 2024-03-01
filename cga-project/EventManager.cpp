#include "EventManager.h"
#include "LoggerUtil.h"
#include <iostream>
#include <fstream>

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

/*Aybike: Some stuff I don't understand here. Check it out again later.*/
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
	bindingsStream.open("Data/InputBindings.cfg");

	// Can't open file.
	if (!bindingsStream.is_open()) {
		std::cout << "Could not read Data/InputBindings.cfg." << std::endl;
		return;
	}

	std::string line;
	while (std::getline(bindingsStream, line)) {
#ifdef _DEBUG
		LoggerUtil::CE_OUTPUT_ERROR(line);
		LoggerUtil::CE_OUTPUT_WARNING(line);
		LoggerUtil::CE_OUTPUT_DEBUG(line);

#endif // _DEBUG
	}
	bindingsStream.close();
}
