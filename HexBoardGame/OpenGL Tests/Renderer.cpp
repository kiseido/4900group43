#include "Renderer.h"
#include "Transformer.h"
#include <iostream>
#include "Component.h"
#include "Utils.h"


namespace {
    constexpr int numVAOs = 1;
    constexpr int numVBOs = 3;
    GLuint vao[numVAOs];
    GLuint vbo[numVBOs];
    GLuint curTexture;
    Mesh* curMesh;
    GLuint renderingProgram;
    float cameraX, cameraY, cameraZ;
    GLuint projLoc, camLoc, tnetLoc, normalLoc;
    GLuint globalAmbLoc, lightAmbLoc, lightDiffLoc, lightSpecLoc, lightPosLoc;
    GLuint matAmbLoc, matDiffLoc, matSpecLoc, matShinLoc;
    int width, height;
    float aspect;
    glm::mat4 projMat, camMat, tnetMat;

    float globalAmb[4] = { 0,0,0,0 };
    float lightAmb[4] = { 0,0,0,0 };
    float lightDiff[4] = { 0,0,0,0 };
    float lightSpec[4] = { 0,0,0,0 };
    float lightPos[3] = { 0,0,0};

    float matAmb[4] = { 0,0,0,0 };
    float matDiff[4] = { 0,0,0,0 };
    float matSpec[4] = { 0,0,0,0 };
}


//GLuint vao[numVAOs];
//GLuint vbo[numVBOs];
//GLuint curTexture = 0;
//Mesh* curMesh = nullptr;

GLuint tnetLocF() { return tnetLoc; }
GLuint projLocF() { return projLoc; }
GLuint camLocF() { return camLoc; }

void Renderer::SetAspectRatio(int width, int height) {
    aspect = (float)width / (float)height;
    projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

void setArray(float* arr, glm::vec4 &vec) {
    arr[0] = vec.x; arr[1] = vec.y; arr[2] = vec.z; arr[3] = vec.w;
}
void setArray(float* arr, glm::vec3 &vec) {
    arr[0] = vec.x; arr[1] = vec.y; arr[2] = vec.z;
}

void Renderer::SetLight(glm::vec4 global_amb, glm::vec3 pos, glm::vec4 amb, glm::vec4 diff, glm::vec4 spec) {
    pos = glm::vec3(camMat * glm::vec4(pos, 1.0));
    setArray(globalAmb, global_amb);
    setArray(lightPos, pos);
    setArray(lightAmb, amb);
    setArray(lightDiff, diff);
    setArray(lightSpec, spec);
    glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmb);
    glProgramUniform3fv(renderingProgram, lightPosLoc, 1, lightPos);
    glProgramUniform4fv(renderingProgram, lightAmbLoc, 1, lightAmb);
    glProgramUniform4fv(renderingProgram, lightDiffLoc, 1, lightDiff);
    glProgramUniform4fv(renderingProgram, lightSpecLoc, 1, lightSpec);
}


void Renderer::Setup() {
    renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");

    glUseProgram(renderingProgram);

    camLoc = glGetUniformLocation(renderingProgram, "camera_matrix");
    tnetLoc = glGetUniformLocation(renderingProgram, "transform_matrix");
    normalLoc = glGetUniformLocation(renderingProgram, "normal_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "projection_matrix");

    globalAmbLoc = glGetUniformLocation(renderingProgram, "globalAmbient");

    lightAmbLoc = glGetUniformLocation(renderingProgram, "light.ambient");
    lightDiffLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
    lightSpecLoc = glGetUniformLocation(renderingProgram, "light.specular");
    lightPosLoc = glGetUniformLocation(renderingProgram, "light.position");

    matAmbLoc = glGetUniformLocation(renderingProgram, "material.ambient");
    matDiffLoc = glGetUniformLocation(renderingProgram, "material.diffuse");
    matSpecLoc = glGetUniformLocation(renderingProgram, "material.specular");
    matShinLoc = glGetUniformLocation(renderingProgram, "material.shininess");

    cameraX = 0.0f; cameraY = 10.0f; cameraZ = 10.0f;

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);


    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);


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
    Model* model = ECS::GetModel(eid);
    if (model->texture != curTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model->texture);

        curTexture = model->texture;
        //std::cout << "loading texture into graphics card" << std::endl;
    }

    Transformer::CalcTNet(eid);
    glm::mat4 tnet = camMat * ECS::GetTransform(eid)->tNet;
    glm::mat4 invTrMat = glm::transpose(glm::inverse(tnet));
    glUniformMatrix4fv(tnetLoc, 1, GL_FALSE, glm::value_ptr(tnet));
    glUniformMatrix4fv(normalLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

    setArray(matAmb, model->material.ambient);
    setArray(matDiff, model->material.diffuse);
    setArray(matSpec, model->material.specular);
    float testMatAmb[4] = { matAmb[0], matAmb[1], matAmb[2], matAmb[3] };
    float testMatDiff[4] = { matDiff[0], matDiff[1], matDiff[2], matDiff[3] };
    float testMatSpec[4] = { matSpec[0], matSpec[1], matSpec[2], matSpec[3] };

    glProgramUniform1f(renderingProgram, matShinLoc, model->material.shininess);
    glProgramUniform4fv(renderingProgram, matAmbLoc, 1, matAmb);
    glProgramUniform4fv(renderingProgram, matDiffLoc, 1, matDiff);
    glProgramUniform4fv(renderingProgram, matSpecLoc, 1, matSpec);


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