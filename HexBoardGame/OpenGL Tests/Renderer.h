#pragma once
#include "ECS.h"
#include <GLFW\glfw3.h>

namespace Renderer
{
    void Setup();

    void SetAspectRatio(int width, int height);
 
    void SetLight(glm::vec4 global_amb, glm::vec3 pos, glm::vec4 amb, glm::vec4 diff, glm::vec4 spec);
    
    void UpdateCamera();
    void SetNormalRendering();
    void SetOutlineRendering();
    void RenderEntity(EntityID eid);
    void RenderPicking(EntityID eid);
    EntityID GetMouseEntity(GLint mouseX, GLint mouseY);
    void RenderAll(ComponentID components = 0);
};

struct RenderOptions {
    int pick;
    glm::vec3 color;
    float normalMod;
    float scaleMod;
};
