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

/*Aybike: Some stuff I don't understand here. Check it out again later.*/
void EventManager::HandleEvent(sf::Event& newEvent)
{
	for (auto& eb_elem : m_eventBindings) {
		EventBinding* eventBinding = eb_elem.second;
		
		for (auto& event_elem : eventBinding->m_events) {
			EventType sfmlEvent = (EventType)newEvent.type;

			//Do we have this type of event recorded?
			if (event_elem.first != sfmlEvent)
				continue; //We don't, it doesn't concern us, ignore.

			//We have it recorded. If it's a keyboard event, check for a matching keycode in our recorded events.
			if (sfmlEvent == EventType::KeyUp || sfmlEvent == EventType::KeyDown) {
				if (event_elem.second.m_eventCode == newEvent.key.code) { //We have a matching keycode.
					if (eventBinding->m_details.m_keyCode != -1) //Aybike: Not sure what's this about???
						eventBinding->m_details.m_keyCode = event_elem.second.m_eventCode;

					++(eventBinding->m_count);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) { //If it's a mouse event, check for matching button code.
				if (event_elem.second.m_eventCode == newEvent.mouseButton.button) {
					eventBinding->m_details.m_mouse.x = newEvent.mouseButton.x;
					eventBinding->m_details.m_mouse.y = newEvent.mouseButton.y;
					if (eventBinding->m_details.m_keyCode != -1)
						eventBinding->m_details.m_keyCode = event_elem.second.m_eventCode;

					++(eventBinding->m_count);
					break;
				}
			}
			else {
				if (sfmlEvent == EventType::MouseWheel)
					eventBinding->m_details.m_mouseWheelDelta = newEvent.mouseWheel.delta;
				else if (sfmlEvent == EventType::WindowResized) {
					eventBinding->m_details.m_size.x = newEvent.size.width;
					eventBinding->m_details.m_size.y = newEvent.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered)
					eventBinding->m_details.m_textEntered = newEvent.text.unicode;

				++(eventBinding->m_count);
			}
		}
	}
}

void EventManager::Update()
{
}

void EventManager::LoadBindings()
{

}
