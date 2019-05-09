#include "Renderer.h"
#include "Transformer.h"
#include <iostream>
#include "Utils.h"




//GLuint Renderer::vao[numVAOs];
//GLuint Renderer::vbo[numVBOs];
//GLuint Renderer::curTexture = 0;
//Mesh* Renderer::curMesh = nullptr;

GLuint Renderer::wtf() {
    return renderingProgram;
}
GLuint Renderer::tnetLocF() { return tnetLoc; }
GLuint Renderer::projLocF() { return projLoc; }
GLuint Renderer::camLocF() { return camLoc; }

void Renderer::SetAspectRatio(int width, int height) {
    aspect = (float)width / (float)height;
    projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

void Renderer::Setup() {
    renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");

    glUseProgram(Renderer::renderingProgram);

    camLoc = glGetUniformLocation(renderingProgram, "camera_matrix");
    tnetLoc = glGetUniformLocation(renderingProgram, "transform_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "projection_matrix");

    cameraX = 0.0f; cameraY = 10.0f; cameraZ = 10.0f;

    glGenVertexArrays(1, Renderer::vao);
    glBindVertexArray(Renderer::vao[0]);
    glGenBuffers(Renderer::numVBOs, Renderer::vbo);


    glBindBuffer(GL_ARRAY_BUFFER, Renderer::vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, Renderer::vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    UpdateCamera();


}

void Renderer::UpdateCamera() {
    camMat = glm::mat4(1.0f);
    camMat = glm::rotate(camMat, Utils::toRadians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    camMat = glm::translate(camMat, glm::vec3(-cameraX, -cameraY, -cameraZ));
    //camMat = glm::rotate(camMat, Utils::toRadians(45.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(camMat));
}

void Renderer::RenderEntity(EntityID eid) {
    Model* model = CompletelyFakeECS::GetModel(eid);
    if (model->texture != curTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model->texture);

        curTexture = model->texture;
        //std::cout << "loading texture into graphics card" << std::endl;
    }

    Transformer::CalcTNet(eid);
    glUniformMatrix4fv(tnetLoc, 1, GL_FALSE, glm::value_ptr(CompletelyFakeECS::GetTransform(eid)->tNet));

    if (model->mesh != curMesh) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, model->mesh->pvalues.size() * 4, &model->mesh->pvalues[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, model->mesh->tvalues.size() * 4, &model->mesh->tvalues[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glBufferData(GL_ARRAY_BUFFER, model->mesh->nvalues.size() * 4, &model->mesh->nvalues[0], GL_STATIC_DRAW);

        curMesh = model->mesh;
        //std::cout << "loading mesh into graphics card" << std::endl;
    }
    glDrawArrays(GL_TRIANGLES, 0, model->mesh->numVertices);
}