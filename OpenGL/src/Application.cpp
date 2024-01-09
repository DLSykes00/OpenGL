#include "Application.h"
#include <string>

void Application::run()
{
    Timer timer;

    while (!m_window.shouldClose())
    {
        m_window.pollEvents();

        m_render.draw(timer.getDeltaTimeS());

        timer.updateCpuTime();
        m_window.swapBuffers();

        timer.update();
        if (timer.getElapsedTimeS() >= 1.0f / m_fpsUpdateRateHz)
        {
            displayFrameInfo(timer.getFrames(), timer.getElapsedTimeS(), timer.getCpuTimeS());
            timer.resetTimer();
        }
    }
}

void Application::displayFrameInfo(int frames, float elapsedTimeS, float cpuTimeS)
{
    glm::vec3 pos = m_render.getCamera().getPosition();
    m_window.setTitle(std::to_string(static_cast<int>(frames / elapsedTimeS)) + " FPS, "
        + std::to_string(1e3 * elapsedTimeS / frames)       + " ms | " +
        + "CPU: " + std::to_string(1e3 * cpuTimeS / frames) + " ms | "
        + "GPU: " + std::to_string(m_render.getGpuTimeMs()) + " ms | "
        + "X: " + std::to_string(pos.x) + ", Y: " + std::to_string(pos.y) + ", Z: " + std::to_string(pos.z));
}
