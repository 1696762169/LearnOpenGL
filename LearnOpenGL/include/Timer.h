#pragma once
#include <vector>
#include <functional>
#include <memory>

/**
 * \brief 定义一些全局的时间常量与事件
 */
class Timer
{
public:
	/**
	* \brief 获取上一帧到当前帧的时间间隔
	*/
	_NODISCARD static float DeltaTime() { return m_DeltaTime; }
	/**
	* \brief 获取当前帧时间
	*/
	_NODISCARD static float CurTime() { return m_Time; }

	static void AddUpdateEvent(const std::shared_ptr<std::function<void()>>& event);
	static void AddUpdateEvent(const std::function<void()>& event);
	static void RemoveUpdateEvent(const std::shared_ptr<std::function<void()>>& event);
	static void Update();

private:
	inline static float m_DeltaTime = 0;
	inline static float m_Time = 0;

	inline static std::vector<std::shared_ptr<std::function<void()>>> m_UpdateEvent = std::vector<std::shared_ptr<std::function<void()>>>();
};

