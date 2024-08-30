#include "Object.h"
#include <glm/gtc/quaternion.hpp>

Object::Object(const std::string& name)
{
	this->name = name;

	position = glm::vec3(0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f);

	m_Components = std::vector<std::shared_ptr<Component>>();
	m_RenderComponents = std::vector<std::shared_ptr<IRender>>();
}

void Object::Render()
{
	for (const auto& renderComponent : m_RenderComponents)
	{
		renderComponent->Render();
	}
}

void Object::Update()
{
	/*for (const auto& component : m_Components)
	{
		component->Update();
	}*/
}

std::shared_ptr<Component> Object::AddComponent(const std::shared_ptr<Component>& component)
{
	m_Components.push_back(component);
	component->object = shared_from_this();

	const auto renderComponent = std::dynamic_pointer_cast<IRender, Component>(component);
	if (renderComponent != nullptr)
	{
		m_RenderComponents.push_back(renderComponent);
	}
	return component;
}

std::shared_ptr<Component> Object::AddComponent(const std::string& addName)
{
	const auto component = Component::Create(addName);
	return AddComponent(component);
}

std::shared_ptr<Component> Object::GetComponent(const std::string& findName)
{
	for (auto& component : m_Components)
	{
		if (component->name == findName)
		{
			return component;
		}
	}
	return nullptr;
}

glm::vec3 Object::GetEulerAngle() const
{
	return glm::eulerAngles(rotation);
}

void Object::SetEulerAngle(const glm::vec3& degree)
{
	rotation = glm::quat(glm::radians(degree));
}

glm::mat4 Object::GetModelMatrix() const
{
	auto ret = glm::mat4(1.0f);
	// 缩放
	ret = glm::scale(ret, scale);
	// 旋转
	ret = ret * glm::mat4_cast(rotation);
	// 位移
	ret = glm::translate(ret, position);
	return ret;
}

Object::Object() : Object("Object") { }
