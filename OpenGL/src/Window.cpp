#include "Window.h"
#include "Input.h"

Window::Window()
{
    setupGLFW();

    glewInit();
    glViewport(0, 0, m_width, m_height);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);

    Input::setWindowSize(m_width, m_height);

    printf(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

Window::~Window()
{
    glfwTerminate();
}

void Window::setupGLFW()
{
    if (!glfwInit()) exit(0);

    glfwWindowHint(GLFW_SAMPLES, m_samplesMSAA); // MSAA
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(m_width, m_height, "Window", NULL, NULL);
    if (!window)
        Window::~Window();

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    glfwSwapInterval(m_vSyncInterval); // V-Sync

    // Setup cursor for camera manipulation
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetCursorPos(window, 0, 0);

    // Setup callbacks
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void GLAPIENTRY Window::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "\nGL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::setKey(key, action != GLFW_RELEASE);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);

    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->setHeight(h);
    win->setWidth(w);
    
    Input::setWindowSize(w, h);
}

void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    Input::setMousePos(static_cast<float>(xpos), static_cast<float>(ypos));
}
