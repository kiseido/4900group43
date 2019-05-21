#pragma once

#include "ECS.h"

namespace ECS {
	namespace Systems {

		using namespace ECS::Engine;

		class System {
		public:
			virtual void Run(const EngineState& lastState, EngineState& newState) = 0;
		};

		class RTPhysics : public System {
			static const int PerPass;
			bool isEnabled = false;
			void ProcessMomentums(const EngineState& lastState, EngineState& newState);
			void ProcessPositions(const EngineState& lastState, EngineState& newState);
			void ProcessRotations(const EngineState& lastState, EngineState& newState);
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};

		class BoardRenderer : public System {
			float opacity;
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};

		class CombatRenderer : public System {
			float opacity;
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};

		class PausedSystemsPack : public System {
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};

		class BoardSystemsPack : public System {
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};

		class CombatSystemsPack : public System {
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};
		class UserInput : public System {
		public:
			UserInput();
			void Run(const EngineState& lastState, EngineState& newState);

			void customGLFWkey_callback(GLFWwindow * window, int key, int scancode, int action, int mods);

			enum UserAction : Mask_t {
				Key		= 0b1 << 0,
				Mouse	= Key << 1,
				Up		= Mouse << 1,
				Down	= Up << 1,
				Left	= Down << 1,
				Right	= Left << 1,
				Shoot	= Right << 1,
				Pause	= Shoot << 1,
				Menu	= Pause << 1,
				Accept	= Menu << 1,
				Exit	= Accept << 1
			};

			struct ActionEvent {
				UserAction action;
				TimeStamp time;
				int keyCode;
				glm::vec2 position;
				ActionEvent(UserAction, TimeStamp, int) ;
				ActionEvent(UserAction, TimeStamp, int, glm::vec2);
			};

		private:
			std::vector<ActionEvent> events;
		};
	}
}