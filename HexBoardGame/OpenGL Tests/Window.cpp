#include "Window.h"
#include "Renderer.h"
#include "Game.h"

namespace {
    int width, height;
    float aspect;
    GLFWwindow* mainWindow;
}


GLFWwindow* Window::Init() {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    mainWindow = glfwCreateWindow(600, 600, "H.E.X.", NULL, NULL);
    glfwMakeContextCurrent(mainWindow);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(mainWindow, window_size_callback);

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


void Window::checkMouseOver(double &mouseX, double &mouseY) {
    double mX, mY;
    glfwGetCursorPos(mainWindow, &mX, &mY);
    mouseX = mX;
    mouseY = height - mY;
}


void Window::window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    aspect = (float)newWidth / (float)newHeight;
    glViewport(0, 0, newWidth, newHeight);
    Renderer::SetAspectRatio(newWidth, newHeight);
}


