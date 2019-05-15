#include "Game.h"
#include "ECS.h"
#include "Renderer.h"
#include "Transformer.h"
#include "Window.h"

EntityID mouseOverEntity;
EntityID selectedPieceEntity;

void Game::GameLoop(double currentTime) {
    Renderer::UpdateCamera();
    double mouseX, mouseY;
    Window::GetMousePosition(mouseX, mouseY);
    mouseOverEntity = Renderer::GetMouseEntity(mouseX, mouseY);

    Renderer::RenderScene();
    Renderer::RenderOutline(mouseOverEntity, 4, Renderer::COLOR_RED);
    if (selectedPieceEntity) Renderer::RenderOutline(selectedPieceEntity, 10, Renderer::COLOR_BLUE);
}

void Game::MouseLeftClick() {
    if (!selectedPieceEntity) {
        if (ECS::HasComponents(mouseOverEntity, ComponentBoardPiece)) {
            selectedPieceEntity = mouseOverEntity;
        }
    }
    else {
        if (ECS::HasComponents(mouseOverEntity, ComponentBoardPosition)) {
            Transformer::SetPosition(selectedPieceEntity, ECS::GetTransform(mouseOverEntity)->position);
        }
    }
}


void Game::MouseRightClick() {
    selectedPieceEntity = 0;
}