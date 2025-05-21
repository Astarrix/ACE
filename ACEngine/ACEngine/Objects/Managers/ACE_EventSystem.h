#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

enum class ACE_EventType
{
	Input,
	Collision,
	ActorSpawned,
	ActorDestroyed,
	Custom
	// Add more as needed
};

struct ACE_Event
{
	ACE_EventType type;
	void* data;
	std::string customType; // For custom events
};

class ACE_EventSystem
{
private:
	using EventCallback = std::function<void(const ACE_Event&)>;
	std::unordered_map<ACE_EventType, std::vector<EventCallback>> listeners;
	std::unordered_map<std::string, std::vector<EventCallback>> customListeners;
	static ACE_EventSystem* instance;

	ACE_EventSystem() = default;

public:
	static ACE_EventSystem* Instance();

	void Subscribe(ACE_EventType type, EventCallback callback);
	void Subscribe(const std::string& customType, EventCallback callback);
	void Unsubscribe(ACE_EventType type, EventCallback callback);
	void Dispatch(const ACE_Event& event);
};
