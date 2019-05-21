#include "Game_old.h"
#include "ECS_old.h"
#include "Renderer.h"
#include "Transformer.h"
#include "Window.h"
#include "BoardManager.h"

EntityID mouseOverEntity;
EntityID selectedPieceEntity;
Board* mainBoard;
Board* combatBoard;
EntityID player;

void Game_old::Start() {
    mainBoard = new Board(5);
    player = ECS_old::CreateEntity(Piece1Model);
    BoardManager::SetBoardPosition(player, mainBoard, 0, 0);
    ECS_old::SetBoardPiece(player, new BoardPiece(2));
}

void Game_old::GameLoop(double currentTime) {
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

void Game_old::MouseLeftClick() {
    if (!selectedPieceEntity) {
        if (ECS_old::HasComponents(mouseOverEntity, ComponentBoardPiece)) {
            selectedPieceEntity = mouseOverEntity;
        }
    }
    else {
        if (ECS_old::HasComponents(mouseOverEntity, ComponentBoardPosition)) {
            BoardPosition* pos = ECS_old::GetBoardPosition(mouseOverEntity);
            if (BoardManager::IsInRange(
                ECS_old::GetBoardPiece(selectedPieceEntity),
                ECS_old::GetBoardPosition(selectedPieceEntity),
                ECS_old::GetBoardPosition(mouseOverEntity))) {
                BoardManager::SetBoardPosition(selectedPieceEntity, mainBoard, pos->x, pos->y);
            }
            //Transformer::SetPosition(selectedPieceEntity, ECS::GetTransform(mouseOverEntity)->position);
        }
    }
}


void Game_old::MouseRightClick() {
    selectedPieceEntity = 0;
}