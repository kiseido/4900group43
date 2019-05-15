#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\soil2.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Entity.h"

namespace Window {
    GLFWwindow* Init();
    void Start();

    bool GetMousePosition(double &mouseX, double &mouseY);
    void framebuffer_size_callback(GLFWwindow* win, int newWidth, int newHeight);
    void window_size_callback(GLFWwindow* win, int newWidth, int newHeight);
    void mouse_position_callback(GLFWwindow* win, double mouseX, double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}