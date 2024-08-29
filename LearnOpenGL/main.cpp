﻿#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "define.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "Vao.h"
#include "Vbo.h"
#include "Component/Mesh.h"

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    // 设置OpenGL版本与Core模式
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    constexpr int WIN_WIDTH = 800, WIN_HEIGHT = 600;
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 加载GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 设定视口
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* _, const int width, const int height)
                                   {
                                       glViewport(0, 0, width, height);
                                   });

    // 初始化Shader
    const GLuint program = Shader::InitShader("good", "good");
    // 初始化绘制数据
    const auto vertex = std::vector<GLfloat> {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    const auto indices = std::vector<GLuint> {
    	0, 1, 3,
        1, 2, 3
    };

    auto vao = Vao();
    const auto vbo = vao.AddVertex(vertex, 8);
    vbo->SetLayout(0, 3, 0);    // 位置
    vbo->SetLayout(1, 3, 3);    // 颜色
    vbo->SetLayout(2, 2, 6);    // UV
    vao.AddIndices(indices);

    // 加载纹理
    Texture avatarTexture("avatar.jpg");

    // 构建物体
    const auto obj = std::make_shared<Object>("Avatar");
    const auto mesh = obj->AddComponent<Mesh>();
    mesh->shaderProgram = program;
    mesh->model = std::make_shared<Vao>(vao);
    mesh->textures.push_back(std::make_shared<Texture>(avatarTexture));

    Scene::Current()->AddObject(obj);

    // 线框模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);    // 处理输入

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 设置背景色
        glClear(GL_COLOR_BUFFER_BIT);

        // 进行渲染
        Scene::Current()->Render();

        glfwSwapBuffers(window);    // 交换缓冲以显示下一帧图像
        glfwPollEvents();   // 处理用户输入事件
    }

    glfwTerminate();
    return 0;
}
