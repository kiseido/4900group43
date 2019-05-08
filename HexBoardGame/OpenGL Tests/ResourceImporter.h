#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\soil2.h>
#include <iostream>
#include <vector>


namespace ResourceImporter
{
    namespace MeshImporter {
        int ImportObj(const char *filePath, int& numVert, std::vector<float>& vert, std::vector<float>& tex, std::vector<float>& norm);
    };
    namespace TextureImporter {
        int ImportTexture(const char *texImagePath, GLuint& tex);
    }
};

