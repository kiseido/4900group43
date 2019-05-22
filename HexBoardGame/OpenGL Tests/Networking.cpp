#include "ECS.h"

namespace ECS {
	namespace Systems {
		Networking::Networking()
		{
		}


		Networking::~Networking()
		{
		}

		void Networking::Run(Engine::EngineStateManager & stateManager)
		{
			TODO;

			if (stateManager.getHistoryLength() > 1)
				stateManager.popEnd();

			stateManager.LastFinishedState++;
		}
	}
}


