#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* window;

public:
	Window();
	~Window();

	void run();

    static void GLAPIENTRY
        MessageCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam);

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
