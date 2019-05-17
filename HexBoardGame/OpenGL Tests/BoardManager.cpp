#include "BoardManager.h"
#include "Utils.h"

float cos60 = glm::cos(Utils::toRadians(60));
float sin60 = glm::sin(Utils::toRadians(60));
float spacing = 0.05;

glm::vec3 BoardManager::GetTransformPosition(Board* board, int x, int y) {
    return glm::vec3((1.0 + spacing) * 1.5 * cos60 * x, 0, (1.0 + spacing) * sin60 * (y + 0.5 * x));
}

std::vector<BoardPosition*> BoardManager::GetPossibleMoves(Board* board, BoardPosition* position, BoardPiece* piece) {
    std::vector<BoardPosition*> moves;
    int dist = piece->movesLeft;
    for (int j = -dist; j <= dist; j++) {
        int y = position->y + j;
        if (y >= -board->boardHeight && y <= board->boardWidth) {
            for (int i = -dist; i <= dist; i++) {
                int x = position->x + i;
                if (x >= -board->boardWidth && x <= board->boardWidth) {

                }
            }
        }
    }
    return moves;
}

bool BoardManager::IsInRange(BoardPiece* piece, BoardPosition* source, BoardPosition* destination) {
    int distX = destination->x - source->x;
    int distY = destination->y - source->y;
    int dist = glm::max(glm::max(glm::abs(distX), glm::abs(distY)), glm::abs(distX+distY));
    std::cout << distX << " " << distY << " " << dist << std::endl;
    return dist <= piece->movesLeft;
    return false;
}

void BoardManager::SetTransformPosition(EntityID eid, Board* board, int x, int y) {
    Transformer::SetPosition(eid, BoardManager::GetTransformPosition(board, x, y));
}

void BoardManager::SetBoardPosition(EntityID eid, Board* board, int x, int y, bool transform) {
    ECS::SetBoardPosition(eid, GetPosition(board, x, y));
    if (transform) {
        SetTransformPosition(eid, board, x, y);
    }
}

BoardPosition* BoardManager::GetPosition(Board* board, int x, int y) {
    return board->board[board->radius + y][board->radius + x];
}