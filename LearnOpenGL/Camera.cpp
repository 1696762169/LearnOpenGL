#include "Camera.h"

#include <iostream>
#include <glm/gtc/quaternion.hpp>

#include "define.h"
#include "Input.h"
#include "Shader.h"
#include "Timer.h"

Camera::Camera() : Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
{
}

Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
{
	this->position = position;
	rotation = glm::quatLookAt(glm::normalize(target - position), up);

	// 监听移动事件
	Timer::AddUpdateEvent([this] { Move(); });
}

/**
 * \brief 更新当前视口矩阵 与 透视矩阵
 */
void Camera::Update() const
{
	// 生成矩阵
	const auto view = glm::mat4_cast(rotation) * glm::translate(glm::mat4(1.0f), -position);
	const auto projection = orthographic ? 
		glm::ortho(0.0f, width, 0.0f, height, near, far) :
		glm::perspective(glm::radians(fov), width / height, near, far);

	// 更新着色器
	Shader::SetUniformMat(SHADER_VIEW, view);
	Shader::SetUniformMat(SHADER_PROJECTION, projection);
}

glm::vec3 Camera::GetEulerAngle() const
{
	return glm::degrees(glm::eulerAngles(rotation));
}

void Camera::SetEulerAngle(const glm::vec3& degree)
{
	const float x = glm::clamp(degree.x, -89.9f, 89.9f);
	const glm::vec3 euler = glm::radians(glm::vec3(x, degree.y, degree.z));
	rotation = glm::quat(euler);
}

void Camera::Move()
{
	// 更新速度
	m_Speed = m_LastMove ? m_Speed + acceleration * Timer::DeltaTime() : baseSpeed;

	// 检查移动方向
	glm::vec3 direction = glm::vec3();
	const glm::mat4 localMatrix = glm::mat4_cast(rotation);
	if (Input::GetKey(GLFW_KEY_W))
		direction += glm::vec3(localMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
	if (Input::GetKey(GLFW_KEY_S))
		direction += glm::vec3(localMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	if (Input::GetKey(GLFW_KEY_D))
		direction += glm::vec3(localMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	if (Input::GetKey(GLFW_KEY_A))
		direction += glm::vec3(localMatrix * glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
	if (Input::GetKey(GLFW_KEY_Q))
		direction += glm::vec3(0.0f, -1.0f, 0.0f);
	if (Input::GetKey(GLFW_KEY_E))
		direction += glm::vec3(0.0f, 1.0f, 0.0f);
	m_LastMove = direction != glm::vec3();

	// 移动
	position += direction * m_Speed * Timer::DeltaTime();
	//std::cout << position.x << " " << position.y << " " << position.z << std::endl;

	// 旋转视角
	const double mouseX = Input::GetMouseDeltaX() / width;
	const double mouseY = Input::GetMouseDeltaY() / height;

	glm::vec3 euler = GetEulerAngle();
	euler += Timer::DeltaTime() * rotateSpeed * glm::vec3(mouseY, mouseX, 0.0f);
	SetEulerAngle(euler);
}
