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
    GLuint renderingProgram;
    float cameraX, cameraY, cameraZ;
    GLuint projLoc, camLoc, tnetLoc, normalLoc;
    GLuint globalAmbLoc, lightAmbLoc, lightDiffLoc, lightSpecLoc, lightPosLoc;
    GLuint matAmbLoc, matDiffLoc, matSpecLoc, matShinLoc;
    GLuint renderOptionsPickLoc, renderOptionsColorLoc, renderOptionsNormModLoc, renderOptionsScaleModLoc;
    int width, height;
    float aspect;
    glm::mat4 projMat, camMat, tnetMat;

    float globalAmb[4] = { 0,0,0,0 };
    float lightAmb[4] = { 0,0,0,0 };
    float lightDiff[4] = { 0,0,0,0 };
    float lightSpec[4] = { 0,0,0,0 };
    float lightPos[3] = { 0,0,0 };

    float matAmb[4] = { 0,0,0,0 };
    float matDiff[4] = { 0,0,0,0 };
    float matSpec[4] = { 0,0,0,0 };

    Model* curModel;
    Texture curTexture;
    Mesh* curMesh;
    Material* curMaterial;
    RenderOptions curOptions;

    float renderOptionsColor[3] = { 0,0,0 };

    void setArray(float* arr, glm::vec4 &vec) {
        arr[0] = vec.x; arr[1] = vec.y; arr[2] = vec.z; arr[3] = vec.w;
    }
    void setArray(float* arr, glm::vec3 &vec) {
        arr[0] = vec.x; arr[1] = vec.y; arr[2] = vec.z;
    }


    void SetRenderingMesh(Mesh* mesh) {
        if (curMesh != mesh) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glBufferData(GL_ARRAY_BUFFER, mesh->pvalues.size() * 4, &mesh->pvalues[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
            glBufferData(GL_ARRAY_BUFFER, mesh->tvalues.size() * 4, &mesh->tvalues[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
            glBufferData(GL_ARRAY_BUFFER, mesh->nvalues.size() * 4, &mesh->nvalues[0], GL_STATIC_DRAW);

            curMesh = mesh;
        }
    }

    void SetRenderingTexture(Texture texture) {
        if (curTexture != texture) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);

            curTexture = texture;
        }
    }

    void SetRenderingMaterial(Material* material) {
        if (curMaterial != material) {
            setArray(matAmb, material->ambient);
            setArray(matDiff, material->diffuse);
            setArray(matSpec, material->specular);
            float testMatAmb[4] = { matAmb[0], matAmb[1], matAmb[2], matAmb[3] };
            float testMatDiff[4] = { matDiff[0], matDiff[1], matDiff[2], matDiff[3] };
            float testMatSpec[4] = { matSpec[0], matSpec[1], matSpec[2], matSpec[3] };

            glProgramUniform1f(renderingProgram, matShinLoc, material->shininess);
            glProgramUniform4fv(renderingProgram, matAmbLoc, 1, matAmb);
            glProgramUniform4fv(renderingProgram, matDiffLoc, 1, matDiff);
            glProgramUniform4fv(renderingProgram, matSpecLoc, 1, matSpec);

            curMaterial = material;
        }
    }

    void SetRenderingModel(Model* model) {
        if (curModel != model) {
            SetRenderingTexture(model->texture);
            SetRenderingMesh(model->mesh);
            SetRenderingMaterial(model->material);
            curModel = model;
        }
    }

    void SetRenderOptionsColor(glm::vec3 color) {
        //if (curOptions.color != color) {
            setArray(renderOptionsColor, color);
            float wut[4] = { renderOptionsColor[0], renderOptionsColor[1], renderOptionsColor[2], renderOptionsColor[3] };
            glProgramUniform3fv(renderingProgram, renderOptionsColorLoc, 1, renderOptionsColor);
            curOptions.color = color;
        //}
    }
    void SetRenderOptionsPick(int pick) {
        //if (curOptions.pick != pick) {
            glProgramUniform1i(renderingProgram, renderOptionsPickLoc, pick);
            curOptions.pick = pick;
        //}
    }
    void SetRenderOptionsNormalMod(float normalMod) {
        //if (curOptions.normalMod != normalMod) {
            glProgramUniform1f(renderingProgram, renderOptionsNormModLoc, normalMod);
            curOptions.normalMod = normalMod;
        //}
    }
    void SetRenderOptionsScaleMod(float scaleMod) {
        //if (curOptions.scaleMod != scaleMod) {
            glProgramUniform1f(renderingProgram, renderOptionsScaleModLoc, scaleMod);
            curOptions.scaleMod = scaleMod;
        //}
    }
    void SetRenderOptions(RenderOptions options) {
        SetRenderOptionsPick(options.pick);
        SetRenderOptionsColor(options.color);
        SetRenderOptionsNormalMod(options.normalMod);
        SetRenderOptionsScaleMod(options.scaleMod);
    }
    
}


//GLuint vao[numVAOs];
//GLuint vbo[numVBOs];
//GLuint curTexture = 0;
//Mesh* curMesh = nullptr;

void Renderer::SetAspectRatio(int w, int h) {
    width = w; height = h;
    aspect = (float)width / (float)height;
    projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
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
    renderOptionsPickLoc = glGetUniformLocation(renderingProgram, "render_options.pick");
    renderOptionsColorLoc = glGetUniformLocation(renderingProgram, "render_options.color");
    renderOptionsNormModLoc = glGetUniformLocation(renderingProgram, "render_options.normalmod");
    renderOptionsScaleModLoc = glGetUniformLocation(renderingProgram, "render_options.scalemod");



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

    SetRenderOptions(RenderOptions{ 0, glm::vec3{1,1,1}, 0, 0 });
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

void Renderer::SetNormalRendering() {
    glDisable(GL_SCISSOR_TEST);
}

void Renderer::SetOutlineRendering() {

}

glm::vec3 EntityToColor(EntityID entity) {
    uint8_t r = entity & 255;
    uint8_t g = (entity >> 8) & 255;
    uint8_t b = (entity >> 16) & 255;
    return glm::vec3(r/255.0, g/255.0, b/255.0);
}
EntityID ColorToEntity(glm::vec3 color) {
    uint8_t r = color.x * 255;
    uint8_t g = color.y * 255;
    uint8_t b = color.z * 255;
    EntityID eid = b;
    eid = eid << 8;
    eid = eid | g;
    eid = eid << 8;
    eid = eid | r;
    return eid;
}

EntityID Renderer::GetMouseEntity(GLint mouseX, GLint mouseY) {
    glEnable(GL_SCISSOR_TEST);
    glScissor(mouseX, height - mouseY, 1, 1);
    EntityID totalEntities = ECS::GetEntityCount();
    SetRenderOptionsPick(1);
    for (EntityID eid = 0; eid < totalEntities; eid++) {
        if (ECS::HasComponents(eid, 0 | ComponentTransform | ComponentModel)) {
            SetRenderOptionsColor(EntityToColor(eid));
            RenderEntity(eid);
        }
    }
    unsigned char pixel[4];
    glReadPixels (mouseX, height - mouseY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    EntityID mouseEntityId = ColorToEntity(glm::vec3(pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0));
    glDisable(GL_SCISSOR_TEST);
    SetRenderOptionsPick(0);
    return mouseEntityId;
}

void Renderer::RenderAll(ComponentID components) {
    EntityID totalEntities = ECS::GetEntityCount();
    for (EntityID eid = 0; eid < totalEntities; eid++) {
        if (ECS::HasComponents(eid, components | ComponentTransform | ComponentModel)) {
            RenderEntity(eid);
        }
    }
}

void Renderer::RenderEntity(EntityID eid) {
    if (ECS::HasComponents(eid, ComponentTransform | ComponentModel)) {
        Model* model = ECS::GetModel(eid);
        SetRenderingModel(model);

        Transformer::CalcTNet(eid);
        glm::mat4 tnet = camMat * ECS::GetTransform(eid)->tNet;
        glm::mat4 invTrMat = glm::transpose(glm::inverse(tnet));
        glUniformMatrix4fv(tnetLoc, 1, GL_FALSE, glm::value_ptr(tnet));
        glUniformMatrix4fv(normalLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

        glDrawArrays(GL_TRIANGLES, 0, model->mesh->numVertices);
    }
}

void Renderer::RenderPicking(EntityID eid) {

    Model* model = ECS::GetModel(eid);


}