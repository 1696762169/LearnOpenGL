#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
#include <filesystem>

#include "Shader.h"

Texture::Texture(const std::string& filePath, const int wrapMode, const int minFilter, const int maxFilter,  const bool mipMap)
{
    // 翻转UV以适应OpenGL坐标系
    stbi_set_flip_vertically_on_load(true);
    // 加载纹理数据
    int width, height, channelCount;
    unsigned char* data = stbi_load(("texture/" + filePath).c_str(), &width, &height, &channelCount, 0);
    if (data == nullptr)
	    throw std::runtime_error("[Texture] Failed to load texture: " + filePath);

    // 生成纹理
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    const int format = channelCount == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    if (mipMap)
		glGenerateMipmap(GL_TEXTURE_2D);

    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);

    // 释放纹理数据
    stbi_image_free(data);
}

Texture::Texture(const std::string& filePath) : Texture(filePath, GL_REPEAT, GL_LINEAR, GL_LINEAR, true)
{
}

void Texture::BindSampler(const std::string& sampler)
{
    // 查找未使用的纹理单元并绑定
    for (int i = 0; i < TEXTURE_COUNT; ++i)
    {
	    if (!m_TextureUnitUsed[i])
	    {
		    m_TextureUnit = i;
			m_TextureUnitUsed[i] = true;
			break;
		}
    }
    if (m_TextureUnit == -1)
	    throw std::runtime_error("[Texture] 没有空余的纹理单元可绑定");

    glActiveTexture(GL_TEXTURE0 + m_TextureUnit); // 激活纹理单元
	glBindTexture(GL_TEXTURE_2D, m_Id); // 绑定纹理对象

    // 绑定采样器
	m_Sampler = std::make_shared<std::string>(sampler);
    Shader::SetUniformInt(sampler, m_TextureUnit);
}