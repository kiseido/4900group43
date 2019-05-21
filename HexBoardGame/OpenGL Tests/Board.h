#pragma once
#include "Component.h"
#include <vector>

class BoardPosition : public Component
{
public:
    int x, y;
    BoardPosition() = default;
    BoardPosition(int x, int y);
    ~BoardPosition() = default;
};

struct BoardPiece : public Component
{
    BoardPiece(int moves);
    int maxMoves;
    int movesLeft;
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