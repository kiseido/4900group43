#include "ECS.h"


namespace ECS {


	void PausedSystemsPack::Run(const EngineState & lastState, EngineState & newState)
	{
		std::cout << "PausedSystemsPack" << std::endl;
	}

	void BoardSystemsPack::Run(const EngineState & lastState, EngineState & newState)
	{
		std::cout << "BoardSystemsPack" << std::endl;
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

	void RTPhysics::Run(const EngineState& lastState, EngineState& newState) {


		ProcessMomentums(lastState, newState);
		ProcessPositions(lastState, newState);
		ProcessRotations(lastState, newState);
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