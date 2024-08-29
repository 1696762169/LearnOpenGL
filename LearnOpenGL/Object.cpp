#include "Object.h"

Object::Object(const std::string& name)
{
	this->name = name;

	position = glm::vec3(0.0f);
	eulerAngle = glm::vec3(0.0f);
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

Object::Object() : Object("Object") { }
