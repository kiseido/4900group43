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


class Board {
    BoardPosition **board;
    Board(int radius);
    Board(int width, int height);
};