#include "Board.h"
#include "ECS.h"
#include "Transformer.h"
#include "BoardManager.h"

BoardPosition::BoardPosition(int x, int y) : x(x), y(y) {
}

BoardPiece::BoardPiece(int moves) : maxMoves(moves), movesLeft(moves) {
}

Board::~Board() {
    for (int j = 0; j < boardHeight; j++) {
        for (int i = 0; i < boardWidth; i++) {
            delete board[j][i];
        }
        delete board[j];
    }
}