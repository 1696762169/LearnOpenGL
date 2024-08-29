#pragma once
#include <string>
#include <glad/glad.h>
#include <vector>

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
	static void SetUniformFloatVec(const std::string& name, const std::vector<float>& value, GLuint program = curProgram);

private:
	static GLint StartSetUniform(const std::string& name, GLuint program);

public:
	GLuint id;	// 编译对象ID
	std::string fileName;	// 文件名称
	ShaderType type;
};

