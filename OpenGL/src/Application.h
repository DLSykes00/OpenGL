#pragma once

#include "Window.h"
#include "Graphics/Render.h"

class Application
{
public:
    void run();

private:
    Window m_window;
    Render m_render;

    int m_fpsUpdateRateHz = 2;

    void displayFrameInfo(int frames, float elapsedTimeS, float cpuTimeS);

    class Timer
    {
    public:
        void update()
        {
            float currentTimeS = static_cast<float>(glfwGetTime());
            m_deltaTimeS = currentTimeS - m_previousTimeS;
            m_elapsedTimeS += m_deltaTimeS;
            m_previousTimeS = currentTimeS;
            m_frames++;
        }
        void resetTimer()    { m_elapsedTimeS = 0; m_cpuTimeS = 0; m_frames = 0; }
        void updateCpuTime() { m_cpuTimeS += static_cast<float>(glfwGetTime()) - m_previousTimeS; }

        int   getFrames()       { return m_frames; }
        float getCpuTimeS()     { return m_cpuTimeS; }
        float getDeltaTimeS()   { return m_deltaTimeS; }
        float getElapsedTimeS() { return m_elapsedTimeS; }

    private:
        float m_previousTimeS = static_cast<float>(glfwGetTime());

        int   m_frames       = 0;
        float m_cpuTimeS     = 0.0f;
        float m_deltaTimeS   = 0.0f;
        float m_elapsedTimeS = 0.0f;
    };
};
