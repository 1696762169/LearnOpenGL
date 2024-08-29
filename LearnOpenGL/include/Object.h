#pragma once
#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "Component/Component.h"
#include "interface/IRender.h"

/**
 * \brief 三维空间中的物体
 */
class Object : public IRender
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
	[[nodiscard]] std::shared_ptr<T> GetComponent();
	[[nodiscard]] std::shared_ptr<Component> GetComponent(const std::string& findName);

public:
	std::string name;

	glm::vec3 position;
	glm::vec3 eulerAngle;
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
