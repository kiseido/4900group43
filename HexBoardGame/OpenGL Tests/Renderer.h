#pragma once
#include "CompletelyFakeECS.h"
#include <GLFW\glfw3.h>

namespace Renderer
{
    void JustRenderThisForMePlease(Model* model);
    namespace {
        constexpr int numVAOs = 1;
        constexpr int numVBOs = 3;
        GLuint vao[numVAOs];
        GLuint vbo[numVBOs];
        GLuint curTexture;
        Mesh* curMesh;
        GLuint renderingProgram;
        float cameraX, cameraY, cameraZ;
        GLuint projLoc, camLoc, tnetLoc;
        int width, height;
        float aspect;
        glm::mat4 projMat, camMat, tnetMat;
    }

    GLuint wtf();
    GLuint camLocF();
    GLuint projLocF();
    GLuint tnetLocF();


    void Setup();

    void SetAspectRatio(int width, int height);
    void UpdateCamera();
    void RenderEntity(EntityID eid);
};

