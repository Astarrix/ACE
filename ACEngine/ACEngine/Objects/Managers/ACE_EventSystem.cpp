#include "ACE_EventSystem.h"

ACE_EventSystem* ACE_EventSystem::instance = nullptr;

ACE_EventSystem* ACE_EventSystem::Instance() // singleton thingamajig
{
	if (!instance)
	{
		instance = new ACE_EventSystem();
	}
	return instance;
}

void ACE_EventSystem::Subscribe(ACE_EventType type, EventCallback callback)
{
	listeners[type].push_back(callback); // add a callback to an array (not an array, but it's like an array per type)
}

void ACE_EventSystem::Subscribe(const std::string& customType, EventCallback callback)
{
	customListeners[customType].push_back(callback); // stick it in the custom event list
}

void ACE_EventSystem::Unsubscribe(ACE_EventType type, EventCallback callback) // not even going to pretend i know how this works 
{
	auto& callbacks = listeners[type];
	callbacks.erase(
		std::remove_if(callbacks.begin(), callbacks.end(),
		               [&callback](const EventCallback& cb)
		               {
			               return cb.target_type() == callback.target_type();
		               }),
		callbacks.end()
	);
}

/*EXAMPLE USAGE
ACE_Event jumpEvent
{
	.type = ACE_EventType::Custom,
	.data = this,
	.customType = "CharacterJump"
};
ACE_EventSystem::Instance()->Dispatch(jumpEvent);
*/
void ACE_EventSystem::Dispatch(const ACE_Event& event)
{
	if (event.type == ACE_EventType::Custom) // if its a custom event (defined in the event data)
	{
		auto iterator = customListeners.find(event.customType); // look through the custom listeners for anything with the same tag
		if (iterator != customListeners.end()) // if it found one
		{
			for (const auto& callback : iterator->second)
			{
				callback(event); // run a callback on the event
			}
		}
	}
	else
	{
		auto iterator = listeners.find(event.type); // grab the list of listeners to the event with this type
		if (iterator != listeners.end()) // if it found one+
		{
			for (const auto& callback : iterator->second)
			{
				callback(event); // run a callback on the event
			}
		}
	}
}
