#include "ECS.h"
#include "Renderer.h"
#include "Window.h"
#include "BoardManager.h"
#include "Transformer.h"


namespace ECS {


	void PausedSystemsPack::Run(const EngineState & lastState, EngineState & newState)
	{
		std::cout << "PausedSystemsPack" << std::endl;
	}

    void EndTurn(EngineState& newState) {
        if (newState.PlayerTurn == Player1)
            newState.PlayerTurn = Player2;
        else
            newState.PlayerTurn = Player1;
        for (EntityID eid : newState.EntityIDs) {
            if (newState.hasComponent(eid, BoardPiece_m)) {
                BoardPiece* piece = newState.BoardPieces.getComponent(eid);
                piece->movesLeft = piece->maxMoves;
            }
        }
    }

    void ProcessPieceOutline(EngineState& newState) {
        for (EntityID eid : newState.EntityIDs) {
            if (newState.hasComponent(eid, TeamAffiliation_m | BoardModel_m | BoardTransform_m)) {
                if (*newState.Teams.getComponent(eid) == newState.PlayerTurn) {
                    Renderer::SetOutline(newState.BoardModels.getComponent(eid), 4, Renderer::LIGHT(Renderer::COLOR_BLACK));
                }
            }
        }
    }

    void ProcessBoardInput(EngineState& newState, EntityID& mouseOver, EntityID& selection) {
        Window::MouseInput::MouseState mouseState = Window::GetMouseState(true);
        if (!selection) {
            mouseOver = Renderer::GetMouseEntity(newState, Window::GetMousePosition, ECS::BoardPosition_m | ECS::BoardPiece_m);
            if (mouseOver && *newState.Teams.getComponent(mouseOver) != newState.PlayerTurn)
                mouseOver = 0;
            if (mouseOver) {
                if (mouseState == Window::MouseInput::LeftButtonDown) {
                    selection = mouseOver;
                }
                Renderer::SetOutline(newState.BoardModels.getComponent(mouseOver), 6, Renderer::LIGHT(Renderer::COLOR_BLUE));
            }
        }
        else {
            mouseOver = Renderer::GetMouseEntity(newState, Window::GetMousePosition, ECS::BoardPosition_m | ECS::TerrainType_m);
            Renderer::SetOutline(newState.BoardModels.getComponent(selection), 10, Renderer::COLOR_BLUE);
            if (mouseOver) {
                BoardPosition* piecePos = newState.BoardPositions.getComponent(selection);
                BoardPosition* tilePos = newState.BoardPositions.getComponent(mouseOver);
                int reach = newState.BoardPieces.getComponent(selection)->movesLeft;
                int dist = BoardManager::GetDistance(piecePos, tilePos);
                bool canMove = reach >= 1 && dist == 1;
                glm::vec3 outlineColor = dist == 0 ? Renderer::COLOR_BLUE : canMove ? Renderer::COLOR_GREEN : dist <= reach ? Renderer::COLOR_YELLOW : Renderer::COLOR_RED;
                Renderer::SetOutline(newState.BoardModels.getComponent(mouseOver), 10, outlineColor);
                if (mouseState == Window::MouseInput::LeftButtonDown && canMove) {
                    newState.addComponent(selection, BoardMovement_m);
                    BoardMovement* mov = newState.BoardMovements.getComponent(selection);
                    mov->startX = piecePos->x;
                    mov->startY = piecePos->y;
                    mov->endX = tilePos->x;
                    mov->endY = tilePos->y;
                    mov->lerp = 0;
                    mov->distance = 1;
                    EntityID enemyID = 0;
                    for (EntityID eid : newState.EntityIDs) {
                        if(newState.hasComponent(eid, BoardPosition_m | BoardPiece_m)){
                            BoardPosition* ebpos = newState.BoardPositions.getComponent(eid);
                            if (ebpos->x == tilePos->x && ebpos->y == tilePos->y) {
                                enemyID = eid;
                            }
                        }
                    }
                    if (enemyID)
                        newState.removeEntity(enemyID);
                }
            }
        }
        if (mouseState == Window::MouseInput::RightButtonDown) {
            selection = 0;
            EndTurn(newState);
        }
    }

    void ProcessBoardMovements(const EngineState & lastState, EngineState & newState) {
        for (EntityID eid : newState.EntityIDs) {
            if ((*newState.ComponentMasks.getComponent(eid) & ComponentMask::BoardMovement_m) == ComponentMask::BoardMovement_m) {
                BoardMovement* mov = newState.BoardMovements.getComponent(eid);
                glm::vec3 startPos = BoardManager::GetTransformPosition(mov->startX, mov->startY);
                glm::vec3 endPos = BoardManager::GetTransformPosition(mov->endX, mov->endY);
                mov->lerp = glm::min(mov->lerp + 0.1f, 1.0f);
                glm::vec3 curPos = startPos + mov->lerp * (endPos - startPos);
                if (mov->lerp == 1) {
                    BoardPosition* bpos = newState.BoardPositions.getComponent(eid);
                    bpos->x = mov->endX;
                    bpos->y = mov->endY;
                    newState.BoardPieces.getComponent(eid)->movesLeft -= mov->distance;
                    newState.removeComponent(eid, BoardMovement_m);
                }
                Transformer::SetPosition(newState.BoardTransforms.getComponent(eid), curPos);
            }
        }
    }

	void BoardSystemsPack::Run(const EngineState & lastState, EngineState & newState)
	{
        newState.BoardPositions = lastState.BoardPositions;
        newState.BoardModels = lastState.BoardModels;
        newState.BoardTransforms = lastState.BoardTransforms;
        newState.BoardPieces = lastState.BoardPieces;
        newState.BoardMovements = lastState.BoardMovements;
        ProcessPieceOutline(newState);
        ProcessBoardInput(newState, mouseOver, selection);
        Renderer::RenderState(newState);
        ProcessBoardMovements(lastState, newState);
		//std::cout << "BoardSystemsPack" << std::endl;
	}

	void CombatSystemsPack::Run(const EngineState & lastState, EngineState & newState)
	{
		std::cout << "CombatSystemsPack" << std::endl;
	}

	void BoardRenderer::Run(const EngineState & lastState, EngineState & newState)
	{
		std::cout << "BoardRenderer" << std::endl;
	}
	void CombatRenderer::Run(const EngineState & lastState, EngineState & newState)
	{
		std::cout << "CombatRenderer" << std::endl;
	}

	/*
	PHYSICS
	*/


	void RTPhysics::ProcessRotations(const EngineState& lastState, EngineState& newState) {

	}

	void RTPhysics::ProcessCollisions(const EngineState& lastState, EngineState& newState) {

	}

	void RTPhysics::Run(const EngineState& lastState, EngineState& newState) {


		ProcessMomentums(lastState, newState);
		ProcessPositions(lastState, newState);
		ProcessRotations(lastState, newState);
		ProcessCollisions(lastState, newState);
	}

	const int RTPhysics::PerPass = 100;

	void RTPhysics::ProcessMomentums(const EngineState& lastState, EngineState& newState) {
		newState.Momentums = lastState.Momentums;
	}

	void RTPhysics::ProcessPositions(const EngineState& lastState, EngineState& newState) {
		//TimeStamp delta = newState.WorldTime - lastState.WorldTime;

		//Momentum temp[PerPass];

		//int length = newState.RealTimePositions.Components.size();

		//auto posMapIter = newState.RealTimePositions.EntityMap.begin();

		//Momentum* pTemp;

		//Position* newPos = &newState.RealTimePositions.Components[0];
		//const Position* oldPos = &lastState.RealTimePositions.Components[0];

		//for (int start = 0; start < length; start += PerPass) {
		//	int end = start + PerPass;
		//	if (end > length)
		//		end = length;

		//	pTemp = temp;

		//	for (int i = start; i < end; ++i) {
		//		Momentum* p = newState.Momentums.getComponent(posMapIter->first);

		//		if (p == nullptr) {
		//			*pTemp = { 0,0,0 };
		//		}
		//		else {
		//			*pTemp = *p * delta;
		//		}
		//		++posMapIter;
		//		++pTemp;
		//	}

		//	pTemp = temp;

		//	for (int i = start; i < end; ++i) {
		//		*newPos = *pTemp + *oldPos;
		//		++newPos;
		//		++pTemp;
		//		++oldPos;
		//	}
		//}
	}

    
    IntroSystem::IntroSystem() {
        //Transformer::SetScale(&BaseTransform, glm::vec3(0.1, 0.1, 0.1));
        BCIT_square_transform.parent = &BaseTransform;
        BCIT_square_model = Resources::GetModel(BCITSquareModel);
        BCIT_b_model = Resources::GetModel(BCITBModel);
        BCIT_c_model = Resources::GetModel(BCITCModel);
        BCIT_i_model = Resources::GetModel(BCITIModel);
        BCIT_t_model = Resources::GetModel(BCITTModel);
    }

    void IntroSystem::Run(const EngineState& lastState, EngineState& newState) {
        newState.BoardPositions = lastState.BoardPositions;
        newState.BoardModels = lastState.BoardModels;
        newState.BoardTransforms = lastState.BoardTransforms;
        newState.BoardPieces = lastState.BoardPieces;
        newState.BoardMovements = lastState.BoardMovements;
        if (newState.WorldTime >= 5)
            newState.status = EngineState::Board;
        Renderer::Clear();
        Renderer::Render(&BCIT_square_model, &BCIT_square_transform);
        Renderer::Render(&BCIT_b_model, &BCIT_b_transform);
        Renderer::Render(&BCIT_c_model, &BCIT_c_transform);
        Renderer::Render(&BCIT_i_model, &BCIT_i_transform);
        Renderer::Render(&BCIT_t_model, &BCIT_t_transform);
        //Transformer::Rotate(&BCIT_square_transform, glm::vec3(0.05, 0, 0));
    }
}