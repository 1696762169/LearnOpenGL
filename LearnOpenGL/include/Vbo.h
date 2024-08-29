#pragma once
#include <glad/glad.h>
#include <vector>

/**
 * \brief VBO (Vertex Buffer Object) 对应的是存放一组顶点的显存 以及解析这些顶点的方式
 */
class Vbo
{
public:
	void BindData(const std::vector<float>& data, GLint vertexSize, GLenum usage = GL_STATIC_DRAW);
	void SetLayout(GLuint layoutIndex, GLint size, int offset, bool normalized = false) const;

	Vbo();
	static void Dispose();

public:
	GLuint id;
	GLsizei dataSize;			// 数据总大小
	GLsizei vertexSize;		// 顶点大小
};

