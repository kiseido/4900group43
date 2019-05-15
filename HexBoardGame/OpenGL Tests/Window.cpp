#include "Window.h"
#include "Renderer.h"
#include "Game.h"
#include "Utils.h"

namespace {
    int width, height;
    double mouseXPos, mouseYPos;
    float aspect;
    GLFWwindow* mainWindow;
}


GLFWwindow* Window::Init() {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    mainWindow = glfwCreateWindow(600, 600, "H.E.X.", NULL, NULL);
    glfwMakeContextCurrent(mainWindow);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    glfwSetWindowSizeCallback(mainWindow, window_size_callback);
    glfwSetCursorPosCallback(mainWindow, mouse_position_callback);
    glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
    glfwSetScrollCallback(mainWindow, scroll_callback);

    glfwGetFramebufferSize(mainWindow, &width, &height);
    aspect = (float)width / (float)height;
    Renderer::SetAspectRatio(aspect);
}

void Window::Start() {
    while (!glfwWindowShouldClose(mainWindow)) {
        Game::GameLoop(glfwGetTime());
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


bool Window::GetMousePosition(double &mouseX, double &mouseY) {
    //double mX, mY;
    //glfwGetCursorPos(mainWindow, &mX, &mY);
    mouseX = mouseXPos;
    mouseY = mouseYPos;
    return mouseXPos >= 0 && mouseXPos < width && mouseYPos >= 0 && mouseYPos < height;
}


void Window::mouse_position_callback(GLFWwindow* win, double mouseX, double mouseY) {
    mouseXPos = mouseX;
    mouseYPos = height - mouseY;
}

void Window::framebuffer_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
}

void Window::window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    aspect = (float)newWidth / (float)newHeight;
    Renderer::SetAspectRatio(aspect);
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        Game::MouseClick();
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Renderer::ChangeCameraZoom(yoffset / 10);
}
