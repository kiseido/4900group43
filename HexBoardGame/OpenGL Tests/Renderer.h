#pragma once
#include "CompletelyFakeECS.h"
#include <GLFW\glfw3.h>

namespace Renderer
{
    namespace {
        GLuint curTexture = 0;
        Mesh* curMesh = nullptr;

        GLuint renderingProgram;
        float cameraX, cameraY, cameraZ;
        GLuint projLoc, camLoc, tnetLoc;
        int width, height;
        float aspect;
        glm::mat4 projMat, camMat, tnetMat;
    }

    #define numVAOs 1
    #define numVBOs 3
    GLuint vao[numVAOs];
    GLuint vbo[numVBOs];

    void SetWindow(GLFWwindow* window);

    void setup();

    void RenderEntity(EntityID eid);
};

