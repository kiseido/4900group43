#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\soil2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp> // glm::value_ptr
#include <glm\gtc\matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "Graphics.h"
#include "Utils.h"
#include "ECS.h"
#include "Renderer.h"
#include "Transformer.h"

using namespace std;

int width, height;
float aspect;
float cos60 = glm::cos(Utils::toRadians(60));
float sin60 = glm::sin(Utils::toRadians(60));
EntityID lastEntity = 0;
EntityID player;


void init(GLFWwindow* window) {
    glfwGetFramebufferSize(window, &width, &height);
    Renderer::SetAspectRatio(width, height);
    aspect = (float)width / (float)height;
    
    double testScale = 0.95;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 15; j++) {
            if (((i == 5 || i == 6) && j < 5) || ((i == 4 || i == 5) && (j >= 5 && j < 10)) || ((i == 5 || i == 6) && (j >= 10 && j < 12)) || ((i == 6 || i == 7) && (j >= 12 && j < 15))) {
                lastEntity = ECS::CreateEntity(WaterTileModel);
            }
            else if (i < 9 || (i < 10 && (j < 5 || j >= 10))) {
                lastEntity = ECS::CreateEntity(GrassTileModel);
            }
            else if (((i == 15 || i == 17) && (j > 10 && j < 13)) || (i == 16 && (j > 10 && j < 14))){
                lastEntity = ECS::CreateEntity(RockTileModel);
            }
            else {
                lastEntity = ECS::CreateEntity(DesertTileModel);
            }
            Transformer::SetPosition(lastEntity, 
                glm::vec3(- 6.666 + 1.5 * cos60 * i, 0, -7.5 + sin60 * (j + 0.5 * (i%2))));
            Transformer::SetScale(lastEntity, glm::vec3(testScale, testScale, testScale));
        }
    }
    player = ECS::CreateEntity(Piece1Model);


    Renderer::Setup();
    Renderer::SetLight(
        glm::vec4{ 0.25f, 0.25f, 0.25f, 1.0f }, 
        glm::vec3{ 0, 1, 1 }, 
        glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f }, 
        glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 
        glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
    );
}

EntityID mouseEntityID;
void checkMouseOver(GLFWwindow* window) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    mouseEntityID = Renderer::GetMouseEntity(mouseX, mouseY);
}

void display(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    checkMouseOver(window);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    Renderer::UpdateCamera();
    //Renderer::RenderEntity(mouseEntityID);
    Transformer::SetPosition(player, glm::vec3(ECS::GetTransform(70)->position));
    bool valid = ECS::HasComponents(mouseEntityID, ComponentTransform);
    if (valid) {
        Transformer::Translate(mouseEntityID, glm::vec3(0, 0.15, 0));
    }
    std::cout << mouseEntityID << std::endl;
    Renderer::RenderAll();
    if (valid) {
        Transformer::Translate(mouseEntityID, glm::vec3(0, -0.15, 0));
    }
    //Renderer::RenderEntity(player);
}

void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    aspect = (float)newWidth / (float)newHeight;
    glViewport(0, 0, newWidth, newHeight);
    Renderer::SetAspectRatio(newWidth, newHeight);
}

int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "H.E.X.", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, window_size_callback);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}