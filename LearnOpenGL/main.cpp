#include <iostream>
#include "gl.h"

#include "global.h"
#include "Timer.h"
#include "Input.h"
#include "Camera.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "Vao.h"
#include "Vbo.h"
#include "Component/Mesh.h"

int main()
{
    // 设置OpenGL版本与Core模式
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    const int winWidth = static_cast<int>(Camera::Current()->width);
    const int winHeight = static_cast<int>(Camera::Current()->height);
    g_Window = glfwCreateWindow(winWidth, winHeight, "LearnOpenGL", nullptr, nullptr);
    if (g_Window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(g_Window);
    Input::Init();

	// 加载GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 设定视口
    glViewport(0, 0, winWidth, winHeight);
    glfwSetFramebufferSizeCallback(g_Window, [](GLFWwindow* _, const int width, const int height)
                                   {
                                       glViewport(0, 0, width, height);
                                       Camera::Current()->width = static_cast<float>(width);
    								   Camera::Current()->height = static_cast<float>(height);
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

    //obj->position = glm::vec3(0.0f, -0.5f, 0.0f);
    //obj->scale = glm::vec3(0.5f);
    //obj->SetEulerAngle(glm::vec3(45.0f, 45.0f, 0.0f));

    Scene::Current()->AddObject(obj);

    // 调整相机
    Camera::Current()->position = glm::vec3(0.0f, 0.0f, 3.0f);
    //Camera::Current()->SetEulerAngle(glm::vec3(45.0f, 0.0f, 0.0f));

    // 线框模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 渲染循环
    while (!glfwWindowShouldClose(g_Window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 设置背景色
        glClear(GL_COLOR_BUFFER_BIT);

        // 进行渲染
        Camera::Current()->Update();
        Scene::Current()->Render();

        glfwSwapBuffers(g_Window);    // 交换缓冲以显示下一帧图像
        glfwPollEvents();   // 处理用户输入事件
        Timer::Update();
    }

    glfwTerminate();
    return 0;
}
