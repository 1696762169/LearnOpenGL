#pragma once
#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

#include "Component/Component.h"
#include "interface/IRender.h"

class Component;

/**
 * \brief 三维空间中的物体
 */
class Object : public IRender, public std::enable_shared_from_this<Object>
{
public:
	Object();
	explicit Object(const std::string& name);

	void Render() override;
	void Update();

	template <class T>
	std::shared_ptr<T> AddComponent();
	std::shared_ptr<Component> AddComponent(const std::shared_ptr<Component>& component);
	std::shared_ptr<Component> AddComponent(const std::string& addName);
	template <class T>
	_NODISCARD std::shared_ptr<T> GetComponent();
	_NODISCARD std::shared_ptr<Component> GetComponent(const std::string& findName);

	_NODISCARD glm::vec3 GetEulerAngle() const;
	void SetEulerAngle(const glm::vec3& degree);
	_NODISCARD glm::mat4 GetModelMatrix() const;

public:
	std::string name;

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

private:
    std::vector<std::shared_ptr<Component>> m_Components;
	std::vector<std::shared_ptr<IRender>> m_RenderComponents;
};

template <class T>
std::shared_ptr<T> Object::AddComponent()
{
	const auto component = std::make_shared<T>();
	return std::dynamic_pointer_cast<T, Component>(AddComponent(component));
}

template <class T>
std::shared_ptr<T> Object::GetComponent()
{
	for (const auto& component : m_Components)
	{
		const auto findComponent = std::dynamic_pointer_cast<T, Component>(component);
		if (findComponent != nullptr)
		{
			return findComponent;
		}
	}
	return nullptr;
}
