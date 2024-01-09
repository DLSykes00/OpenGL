#pragma once

class Input
{
public:
    static bool getKey(int key) { return keys[key]; }
    static void setKey(int key, bool state) { keys[key] = state; }

    static float getMouseX() { return mouseX; }
    static float getMouseY() { return mouseY; }
    static void  setMousePos(float x, float y) { mouseX = x, mouseY = y; }

    static int  getWindowWidth()            { return windowWidth; }
    static int  getWindowHeight()           { return windowHeight; }
    static bool getWindowResized()          { return windowResized; }
    static void setWindowResized(bool b)    { windowResized = b; }
    static void setWindowSize(int x, int y) { windowWidth = x; windowHeight = y; windowResized = true; }
    

private:
    static const int MAX_KEYS = 512;
    static bool keys[MAX_KEYS];

    static float mouseX;
    static float mouseY;

    static int  windowWidth;
    static int  windowHeight;
    static bool windowResized;
};
