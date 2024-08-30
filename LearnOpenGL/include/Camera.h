#pragma once
#include <memory>
#include <glm/fwd.hpp>
#include <glm/detail/type_quat.hpp>

class Camera
{
public:
	Camera();
	Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

	void Update() const;

	_NODISCARD glm::vec3 GetEulerAngle() const;
	void SetEulerAngle(const glm::vec3& degree);

	_NODISCARD static std::shared_ptr<Camera> Current()
	{
		if (m_Current == nullptr)
			m_Current = std::make_shared<Camera>();
		return m_Current;
	}

private:
	void Move();

public:
	bool orthographic = false;

	glm::vec3 position;
	glm::quat rotation;

	// 视口大小
	float width = 800.0f;
	float height = 600.0f;
	float fov = 45.0f;

	// 裁剪面
	float near = 0.1f;
	float far = 100.0f;

	// 移动速度与加速度
	float baseSpeed = 0.1f;
	float acceleration = 0.1f;
	// 旋转速度
	float rotateSpeed = 500.0f;

private:
	inline static std::shared_ptr<Camera> m_Current = nullptr;

	// 当前速度
	float m_Speed = 0.0f;
	// 上一帧是否有在移动
	bool m_LastMove = false;
};
