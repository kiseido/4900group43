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
        Transformer::SetScale(&BaseTransform, glm::vec3(1.5, 1.5, 1.5));
        Transformer::SetRotation(&BaseTransform, glm::vec3(0.785, 0, 0));
        Transformer::SetPosition(&BCIT_b_transform, glm::vec3(-10, 20, 0));
        Transformer::SetPosition(&BCIT_c_transform, glm::vec3(-5, 20, 0));
        Transformer::SetPosition(&BCIT_i_transform, glm::vec3(5, 20, 0));
        Transformer::SetPosition(&BCIT_t_transform, glm::vec3(10, 20, 0));
        Transformer::SetRotation(&DigiPro_plane_transform, glm::vec3(0, 0, 3.1415926));
        
        BCIT_square_transform.parent = &BaseTransform;
        BCIT_b_transform.parent = &BaseTransform;
        BCIT_c_transform.parent = &BaseTransform;
        BCIT_i_transform.parent = &BaseTransform;
        BCIT_t_transform.parent = &BaseTransform;
        DigiPro_plane_transform.parent = &BaseTransform;
        BCIT_square_model = Resources::GetModel(BCITSquareModel);
        BCIT_b_model = Resources::GetModel(BCITBModel);
        BCIT_c_model = Resources::GetModel(BCITCModel);
        BCIT_i_model = Resources::GetModel(BCITIModel);
        BCIT_t_model = Resources::GetModel(BCITTModel);
        DigiPro_plane_model = Resources::GetModel(DigiProModel);
    }

    void IntroSystem::Run(const EngineState& lastState, EngineState& newState) {
        newState.BoardPositions = lastState.BoardPositions;
        newState.BoardModels = lastState.BoardModels;
        newState.BoardTransforms = lastState.BoardTransforms;
        newState.BoardPieces = lastState.BoardPieces;
        newState.BoardMovements = lastState.BoardMovements;
        float increment = 0.25f;
        float stage1 = 0;
        float stage2 = 1;
        float stage3 = stage2 + 0.5 + 4 * increment;
        float stage4 = stage3 + 1;
        float stage5 = stage4 + 1;
        if (newState.WorldTime <= stage2 + 0.2) {
            float f = glm::min(newState.WorldTime, 1.0f);
            Renderer::SetLight(
                glm::vec4{ f/3, f/3, f/3, 1.0f },
                glm::vec3{ 0, 1, 1 },
                glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f },
                glm::vec4{ f, f, f, 1.0f },
                glm::vec4{ f, f, f, 1.0f }
            );
        }
        else if (newState.WorldTime <= stage3) {
            float shake = 0;
            if(newState.WorldTime > stage2 + 0.5 * increment && newState.WorldTime < stage2 + 4.5 * increment)
                shake = glm::max((float)glm::cos((newState.WorldTime - stage2 - 0.1 * increment)*2 *3.1415926/increment) - 0.9f, 0.0f) * 3;
            float blerp = glm::min(newState.WorldTime - (stage2 + 0 * increment), increment) * 1.0f/increment;
            float clerp = glm::min(newState.WorldTime - (stage2 + 1 * increment), increment) * 1.0f/increment;
            float ilerp = glm::min(newState.WorldTime - (stage2 + 2 * increment), increment) * 1.0f/increment;
            float tlerp = glm::min(newState.WorldTime - (stage2 + 3 * increment), increment) * 1.0f/increment;
            Transformer::SetPosition(&BCIT_b_transform, (1 - blerp) * glm::vec3(10, 30, 0));
            Transformer::SetPosition(&BCIT_c_transform, (1 - clerp) * glm::vec3(-5, 30, 0));
            Transformer::SetPosition(&BCIT_i_transform, (1 - ilerp) * glm::vec3(5, 30, 0));
            Transformer::SetPosition(&BCIT_t_transform, (1 - tlerp) * glm::vec3(-10, 30, 0));
            shake *= glm::sign(1 + 2.5 * increment - newState.WorldTime);
            Transformer::SetRotation(&BaseTransform, glm::vec3(0.785, 0, shake));
        }
        else if (newState.WorldTime <= stage4) {
            float rot = -3.1415926;
            if (newState.WorldTime <= stage3 + 0.25)
                rot = glm::sin((glm::max(0.0f, newState.WorldTime - (stage3))) * 2 * 3.1415926);
            else if (newState.WorldTime <= stage3 + 0.5)
                rot = - 3 * 3.1415926 + (3*3.1415926 + 1)*glm::max(0.0, glm::sin((newState.WorldTime - stage3) * 2 * 3.1415926));
            Transformer::SetRotation(&BaseTransform, glm::vec3(0.785, 0, rot));
        }
        else if (newState.WorldTime <= stage5) {
            float f = 1 - glm::max(newState.WorldTime - (stage4), 0.0f);
            Renderer::SetLight(
                glm::vec4{ f / 3, f / 3, f / 3, 1.0f },
                glm::vec3{ 0, 1, 1 },
                glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f },
                glm::vec4{ f, f, f, 1.0f },
                glm::vec4{ f, f, f, 1.0f }
            );
        }
        else if (newState.WorldTime >= stage5) {
            Transformer::SetScale(&BaseTransform, glm::vec3(0, 0, 0));
            Renderer::SetLight(
                glm::vec4{ 0.25f, 0.25f, 0.25f, 1.0f },
                glm::vec3{ 0, 1, 1 },
                glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f },
                glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f },
                glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
            );
            newState.status = EngineState::Board;
        }
        Renderer::Clear();
        Renderer::Render(&BCIT_square_model, &BCIT_square_transform);
        Renderer::Render(&BCIT_b_model, &BCIT_b_transform);
        Renderer::Render(&BCIT_c_model, &BCIT_c_transform);
        Renderer::Render(&BCIT_i_model, &BCIT_i_transform);
        Renderer::Render(&BCIT_t_model, &BCIT_t_transform);
        Renderer::Render(&DigiPro_plane_model, &DigiPro_plane_transform);
        //Transformer::Rotate(&BaseTransform, glm::vec3(0, 0.05, 0));
        //Transformer::Rotate(&BCIT_square_transform, glm::vec3(0, 0.05, 0));
    }
}