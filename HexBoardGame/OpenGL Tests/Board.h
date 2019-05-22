#pragma once
#include <vector>
#include "EntityID.h"

class BoardPosition
{
public:
    int x, y;
    BoardPosition() = default;
    BoardPosition(int x, int y);
    ~BoardPosition() = default;
};

struct BoardPiece {
    BoardPiece(int moves);
    int maxMoves;
    int movesLeft;
};

struct BoardMovement {
    int startX, startY, endX, endY;
    float lerp = 0;
    int distance = 0;
    float speed = 1;
};

struct Board {
    ECS::EntityID ***board;
    int radius;
    int boardHeight;
    int boardWidth;
    ~Board();
    Board() = default;
};