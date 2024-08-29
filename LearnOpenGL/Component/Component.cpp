#include "Component/Component.h"

#include <stdexcept>

#include "define.h"
#include "Component/Mesh.h"

Component::Component()
{
	name = "Component";
}

std::shared_ptr<Component> Component::Create(const std::string& name)
{
	if (name.empty())
	{
		throw std::invalid_argument("待创建的组件名称不能为空");
	}

	if (name == COMPONENT_MESH)
	{
		return std::make_shared<Mesh>();
	}
	throw std::invalid_argument("待创建的组件名称未定义：" + name);
}
