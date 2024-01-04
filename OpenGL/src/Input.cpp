#include "Input.h"

bool Input::keys[MAX_KEYS] = {false};

float Input::mouseX = 0.0f;
float Input::mouseY = 0.0f;

bool Input::windowResized = false;
int Input::windowWidth = 0.0f;
int Input::windowHeight = 0.0f;
