#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Object.h"

/**
 * \brief 表示一组物体的集合
 */
class Scene : public IRender
{
public :
	Scene();

	void Render() override;
	void Update() const;

	void AddObject(const std::shared_ptr<Object>& object);
	bool RemoveObject(const std::shared_ptr<Object>& object);
	bool RemoveObject(const std::string& name);
	[[nodiscard]] std::shared_ptr<Object> Find(const std::string& name) const;

	static void SetCurrent(const std::shared_ptr<Scene>& scene) { m_CurrentScene = scene; }
	[[nodiscard]] static std::shared_ptr<Scene> Current() { return m_CurrentScene; }

private:
	std::vector<std::shared_ptr<Object>> m_Objects;

	inline static std::shared_ptr<Scene> m_CurrentScene = std::make_shared<Scene>();
};

