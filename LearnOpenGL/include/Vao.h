#pragma once
#include <memory>

#include "Vbo.h"
#include <glad/glad.h>
#include <functional>
#include <vector>

#include "Ebo.h"

/**
 * \brief VAO (Vertex Array Object) 对应的是存放一组VBO与EBO的配置
 * 可以通过激活不同的VAO来快速切换需要绘制的顶点组
 */
class Vao
{
public:
	std::shared_ptr<Vbo> AddVertex(const std::vector<float>& data, GLint vertexSize, GLenum usage = GL_STATIC_DRAW);
	std::shared_ptr<Ebo> AddIndices(const std::vector<GLuint>& indices, GLenum usage = GL_STATIC_DRAW);

	Vao();
	void Enable() const;
	static void Dispose();

public:
	GLuint id;
	std::shared_ptr<Vbo> vbo;
	std::shared_ptr<Ebo> ebo;
};

