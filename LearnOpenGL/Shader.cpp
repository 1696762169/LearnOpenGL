#include "Shader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <format>
#include <glad/glad.h>

Shader::Shader(const std::string& fileName)
{
	this->fileName = fileName;
	if (this->fileName.ends_with(".vs"))
	{
		type = ShaderType::Vertex;
	}
	else if (this->fileName.ends_with(".fs"))
	{
		type = ShaderType::Fragment;
	}
	else
	{
		std::cerr << std::format("未知的Shader类型：{}", this->fileName) << std::endl;
		return;
	}

	// 读取文件
	std::string filePath = std::format("shader/{}/{}", type == ShaderType::Vertex ? "vertex" : "fragment", this->fileName);
	const auto ifs = std::ifstream(filePath, std::ios::in);
	if (!ifs)
	{
		std::cerr << std::format("打开失败：{}", filePath) << std::endl;
		return;
	}

	std::ostringstream ss;
	ss << ifs.rdbuf();
	std::string str = ss.str();
	const char* content = str.c_str();

	// 进行编译
	id = glCreateShader(type == ShaderType::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	glShaderSource(id, 1, &content, nullptr);
	glCompileShader(id);

	// 检查错误
	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char logBuffer[1024];
		glGetShaderInfoLog(id, 512, nullptr, logBuffer);
		std::cerr << std::format("编译失败：{}\n{}", filePath, logBuffer) << std::endl;
		return;
	}
}

Shader::Shader(const Shader& other)
{
	id = other.id;
	fileName = other.fileName;
	type = other.type;
}

Shader::Shader(Shader&& other) noexcept
{
	id = other.id;
	fileName = other.fileName;
	type = other.type;
}

Shader& Shader::operator=(const Shader& other)
{
	if (this != &other) {
		id = other.id;
		fileName = other.fileName;
		type = other.type;
	}
	return *this;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other) {
		id = other.id;
		fileName = other.fileName;
		type = other.type;
	}
	return *this;
}

/**
 * \brief 编译Shader并返回程序
 * \param vertex vertex shader文件名
 * \param fragment fragment shader文件名
 */
GLuint Shader::InitShader(const std::string& vertex, const std::string& fragment)
{
	// 编译Shader
	const auto vs = std::make_shared<Shader>(vertex.ends_with(".vs") ? vertex : vertex + ".vs");
	const auto fs = std::make_shared<Shader>(fragment.ends_with(".fs") ? fragment : fragment + ".fs");

	// 链接程序
	const GLuint programId = glCreateProgram();
	glAttachShader(programId, vs->id);
	glAttachShader(programId, fs->id);
	glLinkProgram(programId);

	// 检查错误
	int success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		char logBuffer[1024];
		glGetProgramInfoLog(programId, 1024, nullptr, logBuffer);
		std::cerr << "链接程序失败：\n" << logBuffer << std::endl;
	}

	curProgram = programId;
	return curProgram;
}

void Shader::SetUniformBool(const std::string& name, bool value, GLuint program)
{
	const GLint location = StartSetUniform(name, program);
	glUniform1i(location, static_cast<int>(value));
}

void Shader::SetUniformInt(const std::string& name, int value, GLuint program)
{
	const GLint location = StartSetUniform(name, program);
	glUniform1i(location, value);
}

void Shader::SetUniformFloat(const std::string& name, float value, GLuint program)
{
	const GLint location = StartSetUniform(name, program);
	glUniform1f(location, value);
}

void Shader::SetUniformFloatVec(const std::string& name, const std::vector<float>& value, GLuint program)
{
	const GLint location = StartSetUniform(name, program);
	switch (value.size())
	{
	case 3:
		glUniform3f(location, value[0], value[1], value[2]);
		break;
	case 4:
		glUniform4f(location, value[0], value[1], value[2], value[3]);
		break;
	case 2:
		glUniform2f(location, value[0], value[1]);
		break;
	default:
		glUniform1fv(location, static_cast<GLsizei>(value.size()), value.data());
	}
}

GLint Shader::StartSetUniform(const std::string& name, GLuint program)
{
	const int location = glGetUniformLocation(program, name.c_str());
	if (location == -1)
		throw std::exception(std::format("未找到变量：{}", name).c_str());
	glUseProgram(program);
	return location;
}

Shader::~Shader()
{
	// 链接完毕后删除shader对象
	glDeleteShader(id);
}
