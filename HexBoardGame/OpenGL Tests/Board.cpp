#include "Board.h"
#include "Component.h"
#include "Transformer.h"
#include "ECS.h"
#include "BoardManager.h"
#include "Utils.h"

BoardPosition::BoardPosition(int x, int y) : x(x), y(y) {
}

BoardPiece::BoardPiece(int moves) : maxMoves(moves), movesLeft(moves) {
}

Board::Board(int radius) : radius(radius) {
    boardHeight = 2 * radius + 1;
    boardWidth = 2 * radius + 1;
    board = new BoardPosition**[boardHeight];
    for (int j = -radius; j <= radius; j++) {
        board[radius+j] = new BoardPosition*[boardWidth];
        for (int i = -radius; i <= radius; i++) {
            BoardPosition* curPos = nullptr;
            if (glm::abs(i+j) <= radius) {
                EntityID curTile = ECS::CreateEntity(GrassTileModel);
                BoardManager::SetTransformPosition(curTile, this, i, j);
                curPos = new BoardPosition(i, j);
                ECS::SetBoardPosition(curTile, curPos);
                ECS::AddComponentMask(curTile, ComponentPick);
            }
            board[radius+j][radius+i] = curPos;
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