#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\soil2.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Entity.h"

namespace Window {
    GLFWwindow* Init();
    void Start();

    void checkMouseOver(double &mouseX, double &mouseY);
    void window_size_callback(GLFWwindow* win, int newWidth, int newHeight);
}