#pragma once

#include "ECS.h"

namespace ECS {
	namespace Systems {

		using namespace ECS::Engine;

		class System {
		public:
			virtual void Run(const EngineState& lastState, EngineState& newState, TimeStamp delta) = 0;
		};

		class RTPhysics : public System {
			static const int PerPass;
			bool isEnabled = false;
			void ProcessMomentums(const EngineState& lastState, EngineState& newState);
			void ProcessPositions(const EngineState& lastState, EngineState& newState);
			void ProcessRotations(const EngineState& lastState, EngineState& newState);
		public:
			void Run(const EngineState& lastState, EngineState& newState, TimeStamp delta);
		};

		class BoardRenderer : public System {
			float opacity;
		public:
			void Run(const EngineState& lastState, EngineState& newState, TimeStamp delta);
		};

		class CombatRenderer : public System {
			float opacity;
		public:
			void Run(const EngineState& lastState, EngineState& newState, TimeStamp delta);
		};

		class PausedSystemsPack : public System {
		public:
			void Run(const EngineState& lastState, EngineState& newState, TimeStamp delta);
		};

		class BoardSystemsPack : public System {
		public:
			void Run(const EngineState& lastState, EngineState& newState, TimeStamp delta);
		};

		class CombatSystemsPack : public System {
		public:
			void Run(const EngineState& lastState, EngineState& newState, TimeStamp delta);
		};
	}
}