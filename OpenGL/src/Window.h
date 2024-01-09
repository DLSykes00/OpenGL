#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window();
    ~Window();

    GLFWwindow* getWindow() { return window; }

    void pollEvents()  { glfwPollEvents(); }
    void swapBuffers() { glfwSwapBuffers(window); }
    bool shouldClose() { return glfwWindowShouldClose(window); }
    void setTitle(const std::string& title) { glfwSetWindowTitle(window, title.c_str()); }

    int  getWidth()       { return m_width; }
    int  getHeight()      { return m_height; }
    void setWidth(int w)  { m_width = w; }
    void setHeight(int h) { m_height = h; }

private:
    GLFWwindow* window;

    int m_width  = 1280;
    int m_height = 720;

    int m_samplesMSAA = 4;
    int m_vSyncInterval = 0;

    void setupGLFW();

    static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
        GLsizei length, const GLchar* message, const void* userParam);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};
