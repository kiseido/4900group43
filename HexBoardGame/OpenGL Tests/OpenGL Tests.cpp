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
#include "ECS.h"
#include "Renderer.h"
#include "Transformer.h"
#include "Window.h"

using namespace std;

int width, height;
float aspect;
float cos60 = glm::cos(Utils::toRadians(60));
float sin60 = glm::sin(Utils::toRadians(60));
EntityID lastEntity = 0;
EntityID player;


void init() {
    double testScale = 0.95;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 15; j++) {
            if (((i == 5 || i == 6) && j < 5) || ((i == 4 || i == 5) && (j >= 5 && j < 10)) || ((i == 5 || i == 6) && (j >= 10 && j < 12)) || ((i == 6 || i == 7) && (j >= 12 && j < 15))) {
                lastEntity = ECS::CreateEntity(WaterTileModel);
            }
            else if (i < 9 || (i < 10 && (j < 5 || j >= 10))) {
                lastEntity = ECS::CreateEntity(GrassTileModel);
            }
            else if (((i == 15 || i == 17) && (j > 10 && j < 13)) || (i == 16 && (j > 10 && j < 14))){
                lastEntity = ECS::CreateEntity(RockTileModel);
            }
            else {
                lastEntity = ECS::CreateEntity(DesertTileModel);
            }
            Transformer::SetPosition(lastEntity, 
                glm::vec3(- 6.666 + 1.5 * cos60 * i, 0, -7.5 + sin60 * (j + 0.5 * (i%2))));
            Transformer::SetScale(lastEntity, glm::vec3(testScale, testScale, testScale));
            ECS::AddComponentMask(lastEntity, ComponentBoardPosition);
        }
    }
    player = ECS::CreateEntity(Piece1Model);
    Transformer::SetPosition(player, glm::vec3(ECS::GetTransform(70)->position));
    ECS::AddComponentMask(player, ComponentBoardPiece);


    Renderer::Setup();
}


int main(void) {
    Window::Init();

    init();

    Window::Start();
}