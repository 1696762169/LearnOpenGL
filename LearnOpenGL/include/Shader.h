#pragma once
#include <format>
#include <string>
#include <glad/glad.h>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

enum class ShaderType : unsigned int
{
	Vertex,
	Fragment,
};

/**
 * \brief Shader程序对象
 */
class Shader
{
public:
	Shader(const std::string& fileName);
	~Shader();
	explicit Shader(const Shader& other);
	explicit Shader(Shader&& other) noexcept;
	Shader& operator=(const Shader& other);
	Shader& operator=(Shader&& other) noexcept;

	static GLuint InitShader(const std::string& vertex, const std::string& fragment);
	inline static GLuint curProgram = 0;	// 当前使用的程序

	// 设置变量
	static void SetUniformBool(const std::string& name, bool value, GLuint program = curProgram);
	static void SetUniformInt(const std::string& name, int value, GLuint program = curProgram);
	static void SetUniformFloat(const std::string& name, float value, GLuint program = curProgram);
	static void SetUniformVec(const std::string& name, const std::vector<float>& value, GLuint program = curProgram);
	template<glm::length_t C, glm::length_t R>
	static void SetUniformMat(const std::string& name, const glm::mat<C, R, glm::f32>& value, GLuint program = curProgram);

private:
	static GLint StartSetUniform(const std::string& name, GLuint program);

public:
	GLuint id;	// 编译对象ID
	std::string fileName;	// 文件名称
	ShaderType type;
};

template <glm::length_t C, glm::length_t R>
void Shader::SetUniformMat(const std::string& name, const glm::mat<C, R, glm::f32>& value, GLuint program)
{
	const GLint location = StartSetUniform(name, program);
	const GLfloat* data = glm::value_ptr(value);
	if (C == R)
	{
		switch (C)
		{
		case 4:
			glUniformMatrix4fv(location, 1, GL_FALSE, data);
			break;
		case 3:
			glUniformMatrix3fv(location, 1, GL_FALSE, data);
			break;
		case 2:
			glUniformMatrix2fv(location, 1, GL_FALSE, data);
			break;
		default:
			throw std::runtime_error(std::format("不支持的矩阵大小：{}x{}", C, R));
		}
	}
	else
	{
		switch (C)
		{
		case 4:
			switch (R)
			{
			case 2:
			{
				glUniformMatrix4x2fv(location, 1, GL_FALSE, data);
				break;
			}
			case 3:
			{
				glUniformMatrix4x3fv(location, 1, GL_FALSE, data);
			}
			break;
			default:
				throw std::runtime_error(std::format("不支持的矩阵大小：{}x{}", C, R));
			}
			break;
		case 3:
			switch (R)
			{
			case 2:
			{
				glUniformMatrix3x2fv(location, 1, GL_FALSE, data);
				break;
			}
			case 4:
			{
				glUniformMatrix3x4fv(location, 1, GL_FALSE, data);
				break;
			}
			default:
				throw std::runtime_error(std::format("不支持的矩阵大小：{}x{}", C, R));
			}
			break;
		case 2:
			switch (R)
			{
			case 3:
			{
				glUniformMatrix2x3fv(location, 1, GL_FALSE, data);
				break;
			}
			case 4:
			{
				glUniformMatrix2x4fv(location, 1, GL_FALSE, data);
				break;
			}
			default:
				throw std::runtime_error(std::format("不支持的矩阵大小：{}x{}", C, R));
			}
			break;
		default:
			throw std::runtime_error(std::format("不支持的矩阵大小：{}x{}", C, R));
		}
	}
}

