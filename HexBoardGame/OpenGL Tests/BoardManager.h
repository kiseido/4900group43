#pragma once
#include "ECS.h"

namespace BoardManager {
    glm::vec3 GetTransformPosition(int x, int y);
    void SetTransformFromBoard(Transform* transform, BoardPosition* position);
    bool IsInRange(BoardPiece* piece, BoardPosition* source, BoardPosition* destination);
    std::vector<BoardPosition*> GetPossibleMoves(Board* board, BoardPosition* position, BoardPiece* piece);

}