#include "Vbo.h"

Vbo::Vbo()
{
	dataSize = 0;
	vertexSize = 0;
	glGenBuffers(1, &id);
}

void Vbo::BindData(const std::vector<float>& data, const GLint vertexSize, const GLenum usage)
{
	// 绑定缓冲区并设置数据
	dataSize = data.size() * sizeof(float);
	this->vertexSize = vertexSize;
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data.data(), usage);
	// 此后可以解绑GL_ARRAY_BUFFER 因为VAO已经记录了VBO的数据
	Dispose();
}

void Vbo::SetLayout(const GLuint layoutIndex, const GLint size, const int offset, const bool normalized) const
{
	// 绑定缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, id);
	// 设置数据解析规则
	glVertexAttribPointer(layoutIndex,
						  size, 
						  GL_FLOAT, 
						  normalized,
						  sizeof(float) * vertexSize, 
						  reinterpret_cast<void*>(offset * sizeof(float))
	);
	// 激活属性
	glEnableVertexAttribArray(layoutIndex);
	// 此后可以解绑GL_ARRAY_BUFFER 因为VAO已经记录了VBO的数据
	Dispose();
}

void Vbo::Dispose()
{
	// 释放缓冲
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
