#include "Renderer.h"
#include "Transformer.h"
#include <iostream>
#include "Window.h"
#include "Utils.h"
#include "Entity.h"

float componentscale(float component, float scale) {
    return glm::min(glm::max(0.0f, component+scale), 1.0f);
}
glm::vec3 colorscale(glm::vec3 color, float scale) {
    return glm::vec3(
        componentscale(color.r, scale),
        componentscale(color.g, scale),
        componentscale(color.b, scale)
    );
}

glm::vec3 Renderer::LIGHT(glm::vec3 color) {
    return colorscale(color, 0.5);
}
glm::vec3 Renderer::DARK(glm::vec3 color) {
    return colorscale(color, -0.5);
}

namespace {
    constexpr int numVAOs = 1;
    constexpr int numVBOs = 3;
    GLuint vao[numVAOs];
    GLuint vbo[numVBOs];
    GLuint renderingProgram;
    bool updateCamera;
    bool updateLight;
    float cameraX, cameraY, cameraZ;
    float aspectRatio;
    float cameraZoom = 1.05f;
    GLuint projLoc, camLoc, tnetLoc, normalLoc;
    GLuint globalAmbLoc, lightAmbLoc, lightDiffLoc, lightSpecLoc, lightPosLoc;
    GLuint matAmbLoc, matDiffLoc, matSpecLoc, matShinLoc;
    GLuint renderOptionsSpecialLoc, renderOptionsLightingLoc, renderOptionsColorLoc, renderOptionsNormModLoc, renderOptionsScaleModLoc;
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

    glm::vec3 lightPositionVector;
    void UpdateLightPosition() {
        glm::vec3 pos = glm::vec3(camMat * glm::vec4(lightPositionVector, 1.0));
        setArray(lightPos, pos);
        glProgramUniform3fv(renderingProgram, lightPosLoc, 1, lightPos);
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

    void SetRenderOptionsSpecial(int special, bool force = false) {
        if (force || curOptions.special != special) {
            glProgramUniform1i(renderingProgram, renderOptionsSpecialLoc, special);
            curOptions.special = special;
        }
    }
    void SetRenderOptionsLighting(int lighting, bool force = false) {
        if (force || curOptions.lighting != lighting) {
            glProgramUniform1i(renderingProgram, renderOptionsLightingLoc, lighting);
            curOptions.lighting = lighting;
        }
    }
    void SetRenderOptionsColor(glm::vec3 color, bool force = false) {
        if (force || curOptions.color != color) {
            setArray(renderOptionsColor, color);
            float wut[4] = { renderOptionsColor[0], renderOptionsColor[1], renderOptionsColor[2], renderOptionsColor[3] };
            glProgramUniform3fv(renderingProgram, renderOptionsColorLoc, 1, renderOptionsColor);
            curOptions.color = color;
        }
    }
    void SetRenderOptionsNormalMod(float normalMod, bool force = false) {
        if (force || curOptions.normalMod != normalMod) {
            glProgramUniform1f(renderingProgram, renderOptionsNormModLoc, normalMod);
            curOptions.normalMod = normalMod;
        }
    }
    void SetRenderOptionsScaleMod(float scaleMod, bool force = false) {
        if (force || curOptions.scaleMod != scaleMod) {
            glProgramUniform1f(renderingProgram, renderOptionsScaleModLoc, scaleMod);
            curOptions.scaleMod = scaleMod;
        }
    }
    void SetRenderOptions(RenderOptions options, bool force = false) {
        SetRenderOptionsSpecial(options.special, force);
        SetRenderOptionsLighting(options.lighting, force);
        SetRenderOptionsColor(options.color, force);
        SetRenderOptionsNormalMod(options.normalMod, force);
        SetRenderOptionsScaleMod(options.scaleMod, force);
    }
    
}


void Renderer::Clear() {
    UpdateCamera();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void Renderer::RenderState(ECS::Engine::EngineState& state) {
    Clear();
    RenderAll(state, ECS::ComponentMask::None_m, false, true);
}


//GLuint vao[numVAOs];
//GLuint vbo[numVBOs];
//GLuint curTexture = 0;
//Mesh* curMesh = nullptr;

void Renderer::SetAspectRatio(float aspect) {
    aspectRatio = aspect;
    projMat = glm::perspective(cameraZoom, aspectRatio, 0.1f, 1000.0f);
}

void Renderer::ChangeCameraZoom(float zoom) {
    cameraZoom = glm::min(glm::max(0.25f, cameraZoom + zoom), 2.5f);
    projMat = glm::perspective(cameraZoom, aspectRatio, 0.1f, 1000.0f);
}

void Renderer::SetLight(glm::vec4 global_amb, glm::vec3 pos, glm::vec4 amb, glm::vec4 diff, glm::vec4 spec) {
    lightPositionVector = pos;
    setArray(globalAmb, global_amb);
    setArray(lightAmb, amb);
    setArray(lightDiff, diff);
    setArray(lightSpec, spec);
    glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmb);
    glProgramUniform4fv(renderingProgram, lightAmbLoc, 1, lightAmb);
    glProgramUniform4fv(renderingProgram, lightDiffLoc, 1, lightDiff);
    glProgramUniform4fv(renderingProgram, lightSpecLoc, 1, lightSpec);
    UpdateLightPosition();
}



void Renderer::Setup() {
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, dbuffer->texId, 0);

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
    renderOptionsSpecialLoc = glGetUniformLocation(renderingProgram, "render_options.special");
    renderOptionsLightingLoc = glGetUniformLocation(renderingProgram, "render_options.lighting");
    renderOptionsColorLoc = glGetUniformLocation(renderingProgram, "render_options.color");
    renderOptionsNormModLoc = glGetUniformLocation(renderingProgram, "render_options.normalMod");
    renderOptionsScaleModLoc = glGetUniformLocation(renderingProgram, "render_options.scaleMod");



    cameraX = 0.0f; cameraY = 10.0f; cameraZ = 10.0f;
    cameraZoom = 1.05f;

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

    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    SetRenderOptions(RenderOptions{ 0, 1, glm::vec3{1,1,1}, 0, 0 }, true);
    SetLight(
        glm::vec4{ 0.25f, 0.25f, 0.25f, 1.0f },
        glm::vec3{ 0, 1, 1 },
        glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f },
        glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
        glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
    );
    UpdateCamera();
}

void Renderer::UpdateCamera() {
    camMat = glm::mat4(1.0f);
    camMat = glm::rotate(camMat, Utils::toRadians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    camMat = glm::translate(camMat, glm::vec3(-cameraX, -cameraY, -cameraZ));
    //camMat = glm::rotate(camMat, Utils::toRadians(45.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(camMat));
    UpdateLightPosition();
}



glm::vec3 EntityToColor(ECS::EntityID entity) {
    uint8_t r = entity & 255;
    uint8_t g = (entity >> 8) & 255;
    uint8_t b = (entity >> 16) & 255;
    return glm::vec3(r/255.0, g/255.0, b/255.0);
}
ECS::EntityID ColorToEntity(glm::vec3 color) {
    uint8_t r = uint8_t(color.x * 255);
    uint8_t g = uint8_t(color.y * 255);
    uint8_t b = uint8_t(color.z * 255);
    ECS::EntityID eid = b;
    eid = eid << 8;
    eid = eid | g;
    eid = eid << 8;
    eid = eid | r;
    return eid;
}

ECS::EntityID Renderer::GetMouseEntity(ECS::EngineState& state, bool callback(double& X, double& Y), ECS::ComponentMask mask) {
    double X, Y;
    if (!callback(X, Y))
        return 0;
    return GetMouseEntity(state, X, Y, mask);
}
ECS::EntityID Renderer::GetMouseEntity(ECS::EngineState& state, GLint mouseX, GLint mouseY, ECS::ComponentMask mask) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
    glScissor(mouseX, mouseY, 1, 1);
    SetRenderOptionsSpecial(2);
    SetRenderOptionsLighting(0);
    RenderAll(state, mask | ECS::ComponentMask::ControlPick_m, true);
    unsigned char pixel[4];
    glReadPixels (mouseX, mouseY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    ECS::EntityID mouseEntityId = ColorToEntity(glm::vec3(pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0));
    glDisable(GL_SCISSOR_TEST);
    SetRenderOptionsSpecial(0);
    SetRenderOptionsLighting(1);
    return mouseEntityId;
}


void RenderOutlines(ECS::EngineState& state, std::vector<ECS::EntityID> eidlist) {
    ECS::ComponentContainer<Model>* modelcontainer = nullptr;
    if (state.status == ECS::EngineState::Board) {
        modelcontainer = &state.BoardModels;
    }
    else if (state.status == ECS::EngineState::Combat) {
        modelcontainer = &state.CombatModels;
    }

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    glColorMask(0, 0, 0, 0);
    for (ECS::EntityID eid : eidlist) {
        Renderer::RenderEntity(state, eid, state.status == ECS::EngineState::Board);
    }
    glColorMask(1, 1, 1, 1);


    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x01);
    SetRenderOptionsSpecial(2);
    SetRenderOptionsLighting(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Model* model = nullptr;
    for (ECS::EntityID eid : eidlist) {
        model = modelcontainer->getComponent(eid);
        if (!model)
            continue;
        SetRenderOptionsColor(model->outlineColor);
        glLineWidth(model->outlineWeight);
        model->outlineWeight = 0;
        Renderer::RenderEntity(state, eid, state.status == ECS::EngineState::Board);
    }

    
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    SetRenderOptionsSpecial(0);
    SetRenderOptionsLighting(1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void Renderer::RenderAll(ECS::Engine::EngineState& state, ECS::ComponentMask components, bool entitytocolor, bool outlinecheck) {
    ECS::ComponentMask transformmodel = ECS::ComponentMask::None_m;
    ECS::ComponentContainer<Model>* modelcontainer = nullptr;
    if (state.status == ECS::EngineState::Board) {
        transformmodel = transformmodel | ECS::ComponentMask::BoardTransform_m | ECS::ComponentMask::BoardModel_m;
        modelcontainer = &state.BoardModels;
    }
    else if (state.status == ECS::EngineState::Combat) {
        transformmodel = transformmodel | ECS::ComponentMask::CombatTransform_m | ECS::ComponentMask::CombatModel_m;
        modelcontainer = &state.CombatModels;
    }
    components = components | transformmodel;
    std::vector<ECS::EntityID> outlines;
    for (ECS::EntityID eid : state.EntityIDs) {
        if ((*state.ComponentMasks.getComponent(eid) & components) == components) {
            if (entitytocolor)
                SetRenderOptionsColor(EntityToColor(eid));
            if (outlinecheck && modelcontainer->getComponent(eid)->outlineWeight > 0)
                outlines.push_back(eid);
            RenderEntity(state, eid, true);
        }
    }
    if(outlines.size() > 0)
        RenderOutlines(state, outlines);
}


void Renderer::RenderEntity(ECS::Engine::EngineState& state, ECS::EntityID eid, bool board) {
    Model* model = board ? state.BoardModels.getComponent(eid) : state.BoardModels.getComponent(eid);
    Transform* transform = board ? state.BoardTransforms.getComponent(eid) : state.BoardTransforms.getComponent(eid);
    Render(model, transform);
}

void Renderer::Render(Model* model, Transform* transform) {
    SetRenderingModel(model);

    Transformer::CalcTNet(transform);
    glm::mat4 tnet = camMat * transform->tNet;
    glm::mat4 invTrMat = glm::transpose(glm::inverse(tnet));
    glUniformMatrix4fv(tnetLoc, 1, GL_FALSE, glm::value_ptr(tnet));
    glUniformMatrix4fv(normalLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

    glDrawArrays(GL_TRIANGLES, 0, model->mesh->numVertices);
}

void Renderer::SetOutline(Model* model, uint8_t weight, glm::vec3 color) {
    if (!model)
        return;
    model->outlineWeight = weight;
    model->outlineColor = color;
}