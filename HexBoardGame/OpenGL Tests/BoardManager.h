#pragma once
#include "ECS.h"
#include "Board.h"

namespace BoardManager {

    Board MakeBoard(ECS::EngineState& state, int radius);
    glm::vec3 GetTransformPosition(int x, int y);
    void SetTransformFromBoard(Transform* transform, BoardPosition* position);
    int GetDistance(BoardPosition* source, BoardPosition* destination);
    bool IsInRange(BoardPiece* piece, BoardPosition* source, BoardPosition* destination);
    std::vector<BoardPosition*> GetPossibleMoves(Board* board, BoardPosition* position, BoardPiece* piece);

}