#pragma once
#include "global.h"
#include "Timer.h"

class Input
{
public:
	_NODISCARD static bool GetKey(const int key) { return glfwGetKey(g_Window, key) == GLFW_PRESS; }
	_NODISCARD static double GetMouseX() { return m_MousePos.x; }
	_NODISCARD static double GetMouseY() { return m_MousePos.y; }
	_NODISCARD static double GetMouseDeltaX() { return m_MouseDeltaPos.x; }
	_NODISCARD static double GetMouseDeltaY() { return m_MouseDeltaPos.y; }

	static void Init()
	{
		// 隐藏鼠标 并 记录鼠标位置
		glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(g_Window, [](GLFWwindow* window, double x, double y)
								 {
									 m_MousePos = glm::dvec2(x, y);
								 });

		Timer::AddUpdateEvent([]()
							  {
								  // 添加退出事件
								  if (glfwGetKey(g_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
									  glfwSetWindowShouldClose(g_Window, GLFW_TRUE);

								  // 记录鼠标位移
								  m_MouseDeltaPos = m_MousePos - m_MouseLastPos;
								  m_MouseLastPos = m_MousePos;
							  });
	}

private:
	inline static glm::dvec2 m_MousePos = glm::dvec2();
	inline static glm::dvec2 m_MouseDeltaPos = glm::dvec2();
	inline static glm::dvec2 m_MouseLastPos = glm::dvec2();
};
