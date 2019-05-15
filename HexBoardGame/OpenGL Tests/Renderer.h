#pragma once
#include "ECS.h"
#include <GLFW\glfw3.h>

namespace Renderer
{
    /*hi*/
    void Setup();

    void SetAspectRatio(int width, int height);
    void SetAspectRatio(float a);
 
    void SetLight(glm::vec4 global_amb, glm::vec3 pos, glm::vec4 amb, glm::vec4 diff, glm::vec4 spec);
    
    void RenderScene();

    void UpdateCamera();
    void SetNormalRendering();
    void SetOutlineRendering();
    void RenderEntity(EntityID eid);
    void RenderPicking(EntityID eid);
    void RenderOutline(EntityID eid);
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
