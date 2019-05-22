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


    void ProcessBoardMovements(const EngineState & lastState, EngineState & newState) {
        for (EntityID eid : newState.EntityIDs) {
            if ((*newState.ComponentMasks.getComponent(eid) & ComponentMask::BoardMovement_m) == ComponentMask::BoardMovement_m) {
                BoardMovement* mov = newState.BoardMovements.getComponent(eid);
                glm::vec3 startPos = BoardManager::GetTransformPosition(mov->startX, mov->startY);
                glm::vec3 endPos = BoardManager::GetTransformPosition(mov->endX, mov->endY);
                glm::vec3 curPos = startPos + mov->lerp * (endPos - startPos);
                mov->lerp = glm::min(mov->lerp + 0.05f, 1.0f);
                if (mov->lerp == 1) {
                    BoardPosition* bpos = newState.BoardPositions.getComponent(eid);
                    bpos->x = mov->endX;
                    bpos->y = mov->endY;
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
        Renderer::SetOutline(newState.BoardModels.getComponent(Renderer::GetMouseEntity(newState, Window::GetMousePosition)), 10, Renderer::COLOR_GREEN);
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
}