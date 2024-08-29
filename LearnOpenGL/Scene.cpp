#include "Scene.h"

Scene::Scene()
{
	m_Objects = std::vector<std::shared_ptr<Object>>();
}

void Scene::Render()
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::Update() const
{
	for (const auto& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::AddObject(const std::shared_ptr<Object>& object)
{
	m_Objects.push_back(object);
}

bool Scene::RemoveObject(const std::shared_ptr<Object>& object)
{
	return std::erase(m_Objects, object);
}

bool Scene::RemoveObject(const std::string& name)
{
	return std::erase_if(m_Objects, [&name](const std::shared_ptr<Object>& object)
	{
		return object->name == name;
	});
}

std::shared_ptr<Object> Scene::Find(const std::string& name) const
{
	const auto it = std::ranges::find_if(m_Objects, 
										 [&name](const std::shared_ptr<Object>& object)
	{
		return object->name == name;
	});
	return it == m_Objects.end() ? nullptr : *it;
}
