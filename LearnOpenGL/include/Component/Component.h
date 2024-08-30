#pragma once
#include <memory>
#include <string>

#include "Object.h"

class Object;
/**
 * \brief 物体上的组件基类
 */
class Component
{
public:
	Component();
	virtual ~Component() = default;
	static std::shared_ptr<Component> Create(const std::string& name);
public:
	std::string name;
	std::shared_ptr<Object> object;
};
