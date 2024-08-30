#include "Timer.h"

#include <GLFW/glfw3.h>
//#include <GLFW/glfw3.h>

void Timer::AddUpdateEvent(const std::shared_ptr<std::function<void()>>& event)
{
	m_UpdateEvent.push_back(event);
}

void Timer::AddUpdateEvent(const std::function<void()>& event)
{
	m_UpdateEvent.push_back(std::make_shared<std::function<void()>>(event));
}

void Timer::RemoveUpdateEvent(const std::shared_ptr<std::function<void()>>& event)
{
	std::erase(m_UpdateEvent, event);
}

void Timer::Update()
{
	const auto time = static_cast<float>(glfwGetTime());
	m_DeltaTime = time - m_Time;
	m_Time = time;

	for (const auto& event : m_UpdateEvent)
		event->operator()();
}
