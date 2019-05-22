#include "BoardManager.h"
#include "Utils.h"
#include "Transformer.h"
#include "ECS.h"
#include "Components.h"

float cos60 = glm::cos(Utils::toRadians(60));
float sin60 = glm::sin(Utils::toRadians(60));
float spacing = 0.05;

glm::vec3 BoardManager::GetTransformPosition(int x, int y) {
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

int BoardManager::GetDistance(BoardPosition* source, BoardPosition* destination) {
    int distX = destination->x - source->x;
    int distY = destination->y - source->y;
    return glm::max(glm::max(glm::abs(distX), glm::abs(distY)), glm::abs(distX + distY));
}

bool BoardManager::IsInRange(BoardPiece* piece, BoardPosition* source, BoardPosition* destination) {
    return GetDistance(source, destination) <= piece->movesLeft;
    return false;
}

void BoardManager::SetTransformFromBoard(Transform* transform, BoardPosition* position) {
    Transformer::SetPosition(transform, BoardManager::GetTransformPosition(position->x, position->y));
}


Board BoardManager::MakeBoard(ECS::EngineState& state, int radius) {

    int boardHeight = 2 * radius + 1;
    int boardWidth = 2 * radius + 1;
    Board newboard;
    newboard.board = new ECS::EntityID**[boardHeight];
    for (int j = -radius; j <= radius; j++) {
        newboard.board[radius + j] = new ECS::EntityID*[boardWidth];
        for (int i = -radius; i <= radius; i++) {
            ECS::EntityID* curTile = nullptr;
            if (glm::abs(i + j) <= radius) {
                const ECS::ComponentMask mask = (ECS::ComponentMask)ECS::BoardTileTemplate;
                auto entity = state.NewEntity(mask);

                *entity.boardModel = Resources::GetModel(GrassTileModel);
                *entity.boardPosition = BoardPosition{ i, j };
                *entity.terrainType = ECS::TerrainType::FlatGround;
                BoardManager::SetTransformFromBoard(entity.boardTransform, entity.boardPosition);
                
                //EntityID curTile = ECS_old::CreateEntity(GrassTileModel);
                //BoardManager::SetTransformPosition(curTile, this, i, j);
                //curPos = new BoardPosition(i, j);
                //ECS_old::SetBoardPosition(curTile, curPos);
                //ECS_old::AddComponentMask(curTile, ComponentPick);
            }
            newboard.board[radius + j][radius + i] = curTile;
        }
    }
    return newboard;
}