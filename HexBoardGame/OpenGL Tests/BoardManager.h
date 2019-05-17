#pragma once
#include "Board.h"
#include "ECS.h"
#include "Transformer.h"

namespace BoardManager {
    //float cos60;
    //float sin60;
    glm::vec3 GetTransformPosition(Board* board, int x, int y);
    void SetTransformPosition(EntityID eid, Board* board, int x, int y);
    void SetBoardPosition(EntityID eid, Board* board, int x, int y, bool transform = true);
    BoardPosition* GetPosition(Board* board, int x, int y);
    bool IsInRange(BoardPiece* piece, BoardPosition* source, BoardPosition* destination);
    std::vector<BoardPosition*> GetPossibleMoves(Board* board, BoardPosition* position, BoardPiece* piece);

}