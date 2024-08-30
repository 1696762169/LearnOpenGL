#include "Component/Mesh.h"
#include "define.h"
#include "Shader.h"

Mesh::Mesh()
{
	name = "Mesh";

	shaderProgram = 0;
	model = nullptr;
	textures = std::vector<std::shared_ptr<Texture>>();
}

Mesh::~Mesh() = default;

void Mesh::SetModel(const std::shared_ptr<Vao>& model)
{
	this->model = model;
}

void Mesh::Render()
{
	if (model == nullptr)
	{
		return;
	}
	glUseProgram(shaderProgram);

	// 设置模型矩阵
	if (object)
	{
		const auto modelMatrix = object->GetModelMatrix();
		Shader::SetUniformMat(SHADER_MODEL, modelMatrix);
	}

	// 绑定纹理
	for (size_t i = 0; i < textures.size(); i++)
	{
		textures[i]->BindSampler(SHADER_TEXTURE(i));
	}

	// 绘制模型
	glBindVertexArray(model->id);
	glDrawElements(GL_TRIANGLES, model->ebo->size, GL_UNSIGNED_INT, nullptr);    // 使用EBO绘制

	glUseProgram(0);
}
