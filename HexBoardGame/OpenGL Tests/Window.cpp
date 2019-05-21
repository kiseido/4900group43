#include "Window.h"
#include "Renderer.h"
#include "Game_old.h"
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
        Game_old::GameLoop(Window::GetTime());
        Window::Update();
    }
    Window::Close();
}

double Window::GetTime() {
    return glfwGetTime();
}

bool Window::IsActive() {
    return !glfwWindowShouldClose(mainWindow);
}

void Window::Update() {
    glfwSwapBuffers(mainWindow);
    glfwPollEvents();
}

void Window::Close(){
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
        Game_old::MouseLeftClick();
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        Game_old::MouseRightClick();
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Renderer::ChangeCameraZoom(-yoffset / 10);
}

namespace ECS {
	namespace Systems {
		UserInput::UserInput()
		{
			events.reserve(9999);
		}
		void UserInput::Run(const EngineState & lastState, EngineState & newState)
		{
			int upKey = glfwGetKey(mainWindow, GLFW_KEY_W);
			int leftKey = glfwGetKey(mainWindow, GLFW_KEY_A);
			int downKey = glfwGetKey(mainWindow, GLFW_KEY_S);
			int rightKey = glfwGetKey(mainWindow, GLFW_KEY_D);

			if (newState.status == ECS::EngineState::GameStatus::Combat) {
				
			}

			for (int i = newState.userInputIndex; i < events.size(); ++i) {

			}

			newState.userInputIndex = events.size();
		}

		void UserInput::customGLFWkey_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				if (scancode == GLFW_PRESS)
					events.push_back(ActionEvent(UserAction::Exit, getTime(), key));
				break;
			case GLFW_KEY_ENTER:
				if (scancode == GLFW_PRESS)
					events.push_back(ActionEvent(UserAction::Accept, getTime(), key));
				break;
			case GLFW_MOUSE_BUTTON_1:
				if (scancode == GLFW_PRESS) {
					double x, y;
					glfwGetCursorPos(window, &x, &y);
					events.push_back(ActionEvent(UserAction::Mouse, getTime(), key, {x, y}));
				}
				break;
			default:
				break;
			}
		}

		UserInput::ActionEvent::ActionEvent(UserAction action, TimeStamp time, int keyCode) : action(action), time(time), keyCode(keyCode)
		{
		}

		UserInput::ActionEvent::ActionEvent(UserAction action, TimeStamp time, int keyCode, glm::vec2 position) : action(action), time(time), keyCode(keyCode), position(position)
		{
		}
	}
}