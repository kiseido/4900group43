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
using namespace std;


float cameraX, cameraY, cameraZ;
float objLocX, objLocY, objLocZ;
GLuint renderingProgram;
#define numVAOs 1
#define numVBOs 3
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
GLuint shuttleTexture;

// variable allocation for display
GLuint projLoc, camLoc, tnetLoc;
int width, height;
float aspect;
float test = 0;
glm::mat4 projMat, camMat, tnetMat;

Mesh* myModel = 0;

float toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

void setupVertices(void) {

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);


    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shuttleTexture);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, myModel->pvalues.size() * 4, &myModel->pvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, myModel->tvalues.size() * 4, &myModel->tvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, myModel->nvalues.size() * 4, &myModel->nvalues[0], GL_STATIC_DRAW);
}

void init(GLFWwindow* window) {
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 1.5f;
    objLocX = 0.0f; objLocY = 0.0f; objLocZ = 0.0f;

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    myModel = Resources::GetMesh(HexagonTileMesh);
    setupVertices();
    shuttleTexture = Utils::loadTexture("checker.jpg");
}

void display(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);
    

    camLoc = glGetUniformLocation(renderingProgram, "camera_matrix");
    tnetLoc = glGetUniformLocation(renderingProgram, "transform_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "projection_matrix");

    camMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(camMat));

    tnetMat = glm::mat4(1.0f);
    tnetMat = glm::translate(tnetMat, glm::vec3(objLocX, objLocY - 0.25, objLocZ));
    tnetMat = glm::rotate(tnetMat, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    tnetMat = glm::rotate(tnetMat, toRadians(135.0f + test), glm::vec3(0.0f, 1.0f, 0.0f));
    tnetMat = glm::rotate(tnetMat, toRadians(35.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    test += 0.25f;

    glUniformMatrix4fv(tnetLoc, 1, GL_FALSE, glm::value_ptr(tnetMat));

    glDrawArrays(GL_TRIANGLES, 0, myModel->numVertices);

    //dafuq drawing a second one static

    tnetMat = glm::translate(glm::mat4(1.0f), glm::vec3(objLocX, objLocY + 0.25, objLocZ));
    tnetMat = glm::rotate(tnetMat, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    tnetMat = glm::rotate(tnetMat, toRadians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    tnetMat = glm::rotate(tnetMat, toRadians(35.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glUniformMatrix4fv(tnetLoc, 1, GL_FALSE, glm::value_ptr(tnetMat));
    glDrawArrays(GL_TRIANGLES, 0, myModel->numVertices);
}

void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
    aspect = (float)newWidth / (float)newHeight;
    glViewport(0, 0, newWidth, newHeight);
    projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter6 - program1", NULL, NULL);
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