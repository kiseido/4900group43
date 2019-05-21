#pragma once
#include "ECS_old.h"
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include "ECS.h"

namespace Renderer
{
    constexpr glm::vec3 COLOR_RED = glm::vec3(1, 0, 0);
    constexpr glm::vec3 COLOR_GREEN = glm::vec3(0, 1, 0);
    constexpr glm::vec3 COLOR_BLUE = glm::vec3(0, 0, 1);
    constexpr glm::vec3 COLOR_YELLOW = glm::vec3(1, 1, 0);
    constexpr glm::vec3 COLOR_CYAN = glm::vec3(0, 1, 1);
    constexpr glm::vec3 COLOR_PINK = glm::vec3(1, 0, 1);
    constexpr glm::vec3 COLOR_WHITE = glm::vec3(1, 1, 1);
    constexpr glm::vec3 COLOR_BLACK = glm::vec3(0, 0, 0);
    glm::vec3 LIGHT(glm::vec3 color);
    glm::vec3 DARK(glm::vec3 color);
    
    /*hi*/
    void Setup();

    void SetAspectRatio(float a);
    void ChangeCameraZoom(float zoom);
 
    void SetLight(glm::vec4 global_amb, glm::vec3 pos, glm::vec4 amb, glm::vec4 diff, glm::vec4 spec);
    
    void RenderScene();
    void RenderState(ECS::Engine::EngineState state);

    void UpdateCamera();
    void RenderEntity(EntityID eid);
    void RenderEntity(ECS::Engine::EngineState state, ECS::EntityID eid, bool board);
    void RenderOutline(EntityID eid, float width, glm::vec3 color);
    EntityID GetMouseEntity(GLint mouseX, GLint mouseY);
    void RenderAll(ComponentID components = 0, bool entitytocolor = false);
};

struct RenderOptions {
    int special;
    int lighting;
    glm::vec3 color;
    float normalMod;
    float scaleMod;
};
