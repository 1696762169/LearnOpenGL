#pragma once
#include <vector>
#include <glad/glad.h>


/**
 * \brief EBO (Element Buffer Object) 对应的是顶点的索引
 * 主要目的是降低顶点被重复使用时的开销
 */
class Ebo
{
public:
	void BindData(const std::vector<GLuint>& indices, const GLenum usage = GL_STATIC_DRAW);

	Ebo();
	static void Dispose();

public:
	GLuint id;
	GLsizei size;
};

