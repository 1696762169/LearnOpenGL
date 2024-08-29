#pragma once
#include <memory>
#include <string>

class Component
{
public:
	Component();
	virtual ~Component() = default;
	static std::shared_ptr<Component> Create(const std::string& name);

public:
	std::string name;
};
