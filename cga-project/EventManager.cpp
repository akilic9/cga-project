#include "EventManager.h"
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

/*Aybike: Some stuff I don't understand here. Check it out again later.*/
void EventManager::HandleEvent(sf::Event& newEvent)
{
	for (auto eb_elem : m_eventBindings) {
		EventBinding* eventBinding = eb_elem.second;
		
		for (auto& event_elem : eventBinding->m_events) {
			EventType sfmlEvent = (EventType)newEvent.type;

			//Does the event type match?
			if (event_elem.first != sfmlEvent)
				continue; //No, go next.

			//We have a match. If it's a keyboard event, check for a matching keycode in our recorded events.
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
	if (!m_hasFocus)
		return;

	for (auto& eb_elem : m_eventBindings) {
		EventBinding* eventBinding = eb_elem.second;

		for (auto& event_elem : eventBinding->m_events) {
			switch (event_elem.first) {
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(event_elem.second.m_eventCode))) {

					if (eventBinding->m_details.m_keyCode != -1)
						eventBinding->m_details.m_keyCode = event_elem.second.m_eventCode;
					
					++(eventBinding->m_count);
				}
				break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(event_elem.second.m_eventCode))) {

					if (eb_elem.second->m_details.m_keyCode != -1)
						eventBinding->m_details.m_keyCode = event_elem.second.m_eventCode;

					++(eventBinding->m_count);
				}
				break;
			}
		}

		if (eventBinding->m_events.size() == eventBinding->m_count)
			if (auto callback = m_callbacks.find(eventBinding->m_name); callback != m_callbacks.end())
				callback->second(&eventBinding->m_details);

		eventBinding->m_count = 0;
		eventBinding->m_details.Clear();
	}
}

void EventManager::LoadBindings()
{
	std::string separator = ":";
	std::ifstream bindingsStream;
	bindingsStream.open("Data/InputBindings.cfg");

	// Can't open file.
	if (!bindingsStream.is_open()) {
		std::cout << "Could not read EventBindings.cfg." << std::endl;
		return;
	}

	std::string line;
	while (std::getline(bindingsStream, line)) {
		std::stringstream eventStream(line);
		std::string eventName;
		eventStream >> eventName;
		EventBinding* eBinding = new EventBinding(eventName);

		while (!eventStream.eof()) {
			std::string typeAndCode;
			eventStream >> typeAndCode;
			int start = 0;
			int sepIndex = typeAndCode.find(separator); // Get index of ':'
			if (sepIndex == std::string::npos) { // Cant't find ':', cancel process for this binding.
				std::cout << ("Can't find separator ':' for binding name %s. Canceling process for this binding.", eventName) << std::endl;
				delete eBinding;
				eBinding = nullptr;
				break;
			}

			EventType type = EventType(stoi(typeAndCode.substr(start, sepIndex - start)));
			int code = stoi(typeAndCode.substr(sepIndex + separator.length(), typeAndCode.find(separator, sepIndex + separator.length())));
			EventInfo eventInfo;
			eventInfo.m_eventCode = code;
			eBinding->BindEvent(type, eventInfo);
		}

		if (!AddBinding(eBinding)) // There was a name conflict while adding the binding, cancel.
			delete eBinding;

		eBinding = nullptr; //Aybike: Why?
	}
	bindingsStream.close();
}
