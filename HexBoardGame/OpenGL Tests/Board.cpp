#include "Board.h"
#include "ECS.h"
#include "Transformer.h"
#include "BoardManager.h"

BoardPosition::BoardPosition(int x, int y) : x(x), y(y) {
}

BoardPiece::BoardPiece(int moves) : maxMoves(moves), movesLeft(moves) {
}

Board::Board(int radius) : radius(radius) {
    boardHeight = 2 * radius + 1;
    boardWidth = 2 * radius + 1;
    board = new ECS::EntityID**[boardHeight];
    for (int j = -radius; j <= radius; j++) {
        board[radius+j] = new ECS::EntityID*[boardWidth];
        for (int i = -radius; i <= radius; i++) {
            ECS::EntityID* curTile = nullptr;
            if (glm::abs(i+j) <= radius) {
                //EntityID curTile = ECS_old::CreateEntity(GrassTileModel);
                //BoardManager::SetTransformPosition(curTile, this, i, j);
                //curPos = new BoardPosition(i, j);
                //ECS_old::SetBoardPosition(curTile, curPos);
                //ECS_old::AddComponentMask(curTile, ComponentPick);
            }
            board[radius+j][radius+i] = curTile;
        }
    }
}

Board::~Board() {
    for (int j = 0; j < boardHeight; j++) {
        for (int i = 0; i < boardWidth; i++) {
            delete board[j][i];
        }
        delete board[j];
    }
}