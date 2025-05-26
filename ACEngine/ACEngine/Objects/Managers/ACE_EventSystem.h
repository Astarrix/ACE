#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

enum class ACE_EventType
{
	Input,
	UI,
	Collision,
	ActorSpawned,
	ActorDestroyed,
	Custom
	// Add more as needed
};

struct ACE_Event
{
	ACE_EventType type;
	void* dataBuffer_1;
	void* dataBuffer_2;
	void* dataBuffer_3;
	std::string customType; 
};

class ACE_EventSystem
{
public:
	#define BindCustomCallback(EventName) EventName,[this](const ACE_Event& event)
	
private:
	ACE_EventSystem() = default;
	
	using EventCallback = std::function<void(const ACE_Event&)>;
	std::unordered_map<ACE_EventType, std::vector<EventCallback>> listeners;
	std::unordered_map<std::string, std::vector<EventCallback>> customListeners;
	static ACE_EventSystem* instance;

public:
	static ACE_EventSystem* Instance();

	void Subscribe(ACE_EventType type, EventCallback callback);
	
	/*
	ACE_EventSystem::Instance()->Subscribe(BindCustomCallback("EventName")
	{ EVENT FUNCTION });
	*/
	void Subscribe(const std::string& customType, EventCallback callback);
	void Unsubscribe(ACE_EventType type, EventCallback callback);

	/*
	 
	 */
	void Dispatch(const ACE_Event& event);
};

