#include "Ebo.h"

void Ebo::BindData(const std::vector<GLuint>& indices, const GLenum usage)
{
	size = indices.size() * sizeof(GLuint);  // NOLINT(clang-diagnostic-shorten-64-to-32)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), usage);

	// 注意此处不能在设置完EBO后立即解绑 否则VAO中会丢失GL_ELEMENT_ARRAY_BUFFER的内容
}

Ebo::Ebo()
{
	glGenBuffers(1, &id);
}

void Ebo::Dispose()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
