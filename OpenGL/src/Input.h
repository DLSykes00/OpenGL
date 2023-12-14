#pragma once

class Input
{
public:
	static bool getKey(int key) { return keys[key]; };
	static void setKey(int key, bool state) { keys[key] = state; };

	static void setWindowResize(int x, int y) { wx = x; wy = y; windowResized = true; };

	static void setWindowResized(bool b) { windowResized = b; };
	static bool getWindowResized() { return windowResized; };
	static int getWx() { return wx; };
	static int getWy() { return wy; };

private:
	static const int MAX_KEYS = 512;
	static bool keys[MAX_KEYS];

	// Temporary way of passing window width/height to camera
	static bool windowResized;
	static int wx;
	static int wy;
};
