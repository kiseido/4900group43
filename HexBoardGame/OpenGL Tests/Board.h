#pragma once
#include "Component.h"
#include "Entity.h"
#include <vector>

class BoardPosition : public Component
{
public:
    int x, y;
    BoardPosition(int x, int y);
    ~BoardPosition() = default;
    std::vector<EntityID> elements;
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