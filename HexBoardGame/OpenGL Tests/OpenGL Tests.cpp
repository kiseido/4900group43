#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\soil2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp> // glm::value_ptr
#include <glm\gtc\matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "Graphics.h"
#include "Utils.h"
#include "ECS_old.h"
#include "Transformer.h"
#include "Renderer.h"
#include "Window.h"
#include "Game_old.h"
#include "ECS.h"
#include "Engine.h"
#include "Systems.h"

#define PRINTSIZE(x) std::cout << #x << " size = " << sizeof(x) << std::endl

int maain(void) {
    PRINTSIZE(glm::vec3);
    PRINTSIZE(glm::mat4);
    PRINTSIZE(glm::ivec2);
    PRINTSIZE(bool);
    PRINTSIZE(Transform*);
    PRINTSIZE(Transform);
    PRINTSIZE(Component);
    PRINTSIZE(Model);
    PRINTSIZE(BoardPiece);
    PRINTSIZE(BoardPosition);




    Window::Init();
    Renderer::Setup();
    Game_old::Start();

    Window::Start();

    return 0;
}