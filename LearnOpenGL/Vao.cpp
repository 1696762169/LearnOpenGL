#include "Vao.h"

std::shared_ptr<Vbo> Vao::AddVertex(const std::vector<float>& data, GLint vertexSize, GLenum usage)
{
	Enable();
	// 构建VBO
	vbo = std::make_shared<Vbo>();
	vbo->BindData(data, vertexSize, usage);
	return vbo;
}

std::shared_ptr<Ebo> Vao::AddIndices(const std::vector<GLuint>& indices, const GLenum usage)
{
	Enable();
	// 构建EBO
	ebo = std::make_shared<Ebo>();
	ebo->BindData(indices, usage);
	return ebo;
}

Vao::Vao()
{
	glGenVertexArrays(1, &id);
}

void Vao::Enable() const
{
	glBindVertexArray(id);
}

void Vao::Dispose()
{
	glBindVertexArray(0);
}
