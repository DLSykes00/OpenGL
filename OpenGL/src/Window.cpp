#include "Window.h"
#include "Input.h"
#include <iostream>

Window::Window()
{
    /* Initialize GLFW */
    if (!glfwInit())
        exit(0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Window", NULL, NULL);
    if (!window)
        Window::~Window();

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    glewInit();

    glfwSwapInterval(1); // v-sync

    glViewport(0, 0, width, height);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glClearColor(0.04f, 0.07f, 0.1f, 1.0f);

    glDebugMessageCallback(MessageCallback, 0);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    std::cout << glGetString(GL_VERSION) << std::endl;
}

Window::~Window()
{
    glfwTerminate();
}

void GLAPIENTRY Window::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "\nGL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::setKey(key, action != GLFW_RELEASE);
}

// Set viewport to new window size and update projection matrix aspect ratio
void Window::framebufferSizeCallback(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);

    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->setHeight(h);
    win->setWidth(w);
    
    Input::setWindowResize(w, h);
}
