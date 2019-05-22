#pragma once
#include <vector>

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
    int startX, startY, nextX, nextY, endX, endY;
    float speed = 1;
    float lerp = 0;
};

struct Board {
    BoardPosition ***board;
    int radius;
    int boardHeight;
    int boardWidth;
    ~Board();
    Board(int radius);
    Board(int width, int height);
};