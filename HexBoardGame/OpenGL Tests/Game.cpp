#include "Game.h"
#include "ECS.h"
#include "Renderer.h"
#include "Transformer.h"
#include "Window.h"
#include "BoardManager.h"

EntityID mouseOverEntity;
EntityID selectedPieceEntity;
Board* mainBoard;
Board* combatBoard;
EntityID player;

void Game::Start() {
    mainBoard = new Board(5);
    player = ECS::CreateEntity(Piece1Model);
    BoardManager::SetBoardPosition(player, mainBoard, 0, 0);
    ECS::SetBoardPiece(player, new BoardPiece(2));
}

void Game::GameLoop(double currentTime) {
    Renderer::UpdateCamera();
    double mouseX, mouseY;
    Window::GetMousePosition(mouseX, mouseY);
    mouseOverEntity = Renderer::GetMouseEntity(mouseX, mouseY);

    Renderer::RenderScene();
    Renderer::RenderOutline(mouseOverEntity, 4, Renderer::COLOR_RED);
    if (selectedPieceEntity) Renderer::RenderOutline(selectedPieceEntity, 10, Renderer::LIGHT(Renderer::COLOR_BLUE));
    std::vector<BoardPosition> walkingRange;
    for (BoardPosition boardpos : walkingRange) {

    }
}

void Game::MouseLeftClick() {
    if (!selectedPieceEntity) {
        if (ECS::HasComponents(mouseOverEntity, ComponentBoardPiece)) {
            selectedPieceEntity = mouseOverEntity;
        }
    }
    else {
        if (ECS::HasComponents(mouseOverEntity, ComponentBoardPosition)) {
            BoardPosition* pos = ECS::GetBoardPosition(mouseOverEntity);
            if (BoardManager::IsInRange(
                ECS::GetBoardPiece(selectedPieceEntity),
                ECS::GetBoardPosition(selectedPieceEntity),
                ECS::GetBoardPosition(mouseOverEntity))) {
                BoardManager::SetBoardPosition(selectedPieceEntity, mainBoard, pos->x, pos->y);
            }
            //Transformer::SetPosition(selectedPieceEntity, ECS::GetTransform(mouseOverEntity)->position);
        }
    }
}


void Game::MouseRightClick() {
    selectedPieceEntity = 0;
}