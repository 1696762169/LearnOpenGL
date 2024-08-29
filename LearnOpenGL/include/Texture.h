#pragma once
#include <memory>
#include <string>
#include <glad/glad.h>

class Texture
{
public:
	void BindSampler(const std::string& sampler);

	explicit Texture(const std::string& filePath);
	explicit Texture(const std::string& filePath, int wrapMode, int minFilter, int maxFilter, bool mipMap);

	[[nodiscard]] GLuint Id() const { return m_Id; }
	[[nodiscard]] int TextureUnit() const { return m_TextureUnit; }
	[[nodiscard]] std::shared_ptr<std::string> Sampler() const { return m_Sampler; }

public:
	constexpr static int TEXTURE_COUNT = 16;

private:
	GLuint m_Id;
	int m_TextureUnit = -1;
	std::shared_ptr<std::string> m_Sampler = nullptr;

	inline static bool m_TextureUnitUsed[TEXTURE_COUNT] = { false };
};

