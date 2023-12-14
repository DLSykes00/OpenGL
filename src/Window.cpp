#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include <iostream>

#define _PI 3.14159265358979323846

Window::Window()
{
    /* Initialize GLFW */
    if (!glfwInit())
        exit(0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 720, "Window", NULL, NULL);
    if (!window)
        Window::~Window();

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    glfwSwapInterval(1);

    glViewport(0, 0, 720, 720);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);

    glfwSetKeyCallback(window, key_callback);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glClearColor(0.04f, 0.07f, 0.1f, 1.0f);

    std::cout << glGetString(GL_VERSION) << std::endl;
}

Window::~Window()
{
    glfwTerminate();
}

void Window::run()
{
    Texture texture("Resources/Textures/test.png");
    texture.bindTexture(0);

    Shader shader;
    shader.useShader();
    shader.setUniform1i("u_Texture", 0);

    Render render;
    float cubeAngle = 0.0f;

    Camera camera;

    int frames = 0;
    double currentTime;
    double deltaTime = 0.0;
    double elapsedTime = 0.0;
    double previousTime = 0.0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;
        elapsedTime += deltaTime;

        if (elapsedTime >= 1.0)
        {
            std::string windowTitle = "FPS: " + std::to_string(frames);
            glfwSetWindowTitle(window, windowTitle.c_str());

            elapsedTime = 0.0;
            frames = 0;
        }
        frames++;

        // Render here 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Doesn't belong here long-term!
        cubeAngle += 0.5f;
        if (cubeAngle >= 360.0f)
            cubeAngle -= 360.0f;

        camera.updateCamera();
        std::cout << "angle|x|y|z: " << camera.yRot << " | " << camera.x << " | " << camera.y << " | " << camera.z << std::endl;

        render.drawCube();

        shader.setProjectionMatrix(cubeAngle, camera.x, camera.y, camera.z, camera.xRot, camera.yRot);

        glDrawElementsInstanced(GL_TRIANGLES, render.getVertCount(), GL_UNSIGNED_INT, nullptr, render.getInstanceCount());
        // Swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
}

void GLAPIENTRY Window::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "\nGL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::key = key;
    Input::action = action;
}









