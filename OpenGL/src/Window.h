#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window();
	~Window();

    GLFWwindow* getWindow() { return window; };

    void pollEvents() { glfwPollEvents(); };
    void swapBuffers() { glfwSwapBuffers(window); };
    bool shouldClose() { return glfwWindowShouldClose(window); };
    void setTitle(const std::string& title) { glfwSetWindowTitle(window, title.c_str()); };

    int getWidth() { return width; };
    void setWidth(int w) { width = w; calculateAR(); };
    int getHeight() { return height; };
    void setHeight(int h) { height = h; calculateAR(); };
    float getAspectRatio() { return aspectRatio; };

private:
    GLFWwindow* window;

    static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
        GLsizei length, const GLchar* message, const void* userParam);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    void calculateAR() { aspectRatio = static_cast<float>(width) / static_cast<float>(height); };

    int width = 720;
    int height = 720;
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
};
