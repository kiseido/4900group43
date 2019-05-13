#pragma once
#include "ECS.h"
#include <GLFW\glfw3.h>

namespace Renderer
{
    void Setup();

    void SetAspectRatio(int width, int height);
 
    void SetLight(glm::vec4 global_amb, glm::vec3 pos, glm::vec4 amb, glm::vec4 diff, glm::vec4 spec);
    
    void UpdateCamera();
    void RenderEntity(EntityID eid);
};

