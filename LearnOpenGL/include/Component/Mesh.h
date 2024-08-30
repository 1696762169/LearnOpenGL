#pragma once
#include <memory>

#include "Component.h"
#include "Texture.h"
#include "Vao.h"
#include "interface/IRender.h"

/**
 * \brief 可渲染的网格
 */
class Mesh final : public Component, public IRender
{
public:
	Mesh();
	~Mesh() override;
	void SetModel(const std::shared_ptr<Vao>& model);
	void Render() override;

public:
	GLuint shaderProgram;

	std::shared_ptr<Vao> model;
	std::vector<std::shared_ptr<Texture>> textures;
};
