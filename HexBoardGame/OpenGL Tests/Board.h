#pragma once
#include "Component.h"


class BoardPosition : public Component
{
public:
    BoardPosition();
    ~BoardPosition() = default;
};



class Board {
    BoardPosition **board;
    Board(int radius);
    Board(int width, int height);
};