#include "EventManager.h"

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

void EventManager::AddBinding(EventBinding* eventBinding)
{
	if (m_eventBindings.find(eventBinding->m_name) != m_eventBindings.end())
		return;

	m_eventBindings[eventBinding->m_name];
}

void EventManager::RemoveBinding(std::string bindingName)
{
	if (auto binding = m_eventBindings.find(bindingName); binding != m_eventBindings.end()) {
		delete binding->second;
		binding->second = nullptr;
		m_eventBindings.erase(binding);
	}
}

void EventManager::SetFocus(const bool& isFocused)
{
}

void EventManager::HandleEvent(sf::Event& event)
{
}

void EventManager::Update()
{
}

void EventManager::LoadBindings()
{

}
