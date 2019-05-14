#pragma once
#include "Board.h";
#include "ECS.h";

namespace BoardManager {
    void SetPosition(EntityID eid, int x, int y);
    void SetPosition(EntityID eid, BoardPosition* position);
    BoardPosition* GetPosition(EntityID eid);
}