#include "Renderer.h"
#include <iostream>
#include "Utils.h"

void Renderer::SetWindow(GLFWwindow* window) {

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

void Renderer::setup() {
    renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 1.5f;

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);


    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Renderer::RenderEntity(EntityID eid) {
    Model *model = CompletelyFakeECS::GetModel(eid);
    if (model->texture != curTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model->texture);
        std::cout << "loading texture into graphics card" << std::endl;
    }

    glUniformMatrix4fv(tnetLoc, 1, GL_FALSE, glm::value_ptr(tnetMat));

    if (model->mesh != curMesh) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, model->mesh->pvalues.size() * 4, &model->mesh->pvalues[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, model->mesh->tvalues.size() * 4, &model->mesh->tvalues[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glBufferData(GL_ARRAY_BUFFER, model->mesh->nvalues.size() * 4, &model->mesh->nvalues[0], GL_STATIC_DRAW);
        std::cout << "loading mesh into graphics card" << std::endl;
    }
}