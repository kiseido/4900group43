#pragma once

#include "ECS.h"

namespace ECS {
	namespace Systems {

		using namespace ECS::Engine;

		// Systems interface to provide intellisense and a standard to work from
		class System {
		public:
			virtual void Run(const EngineState& lastState, EngineState& newState) = 0;
		};

		// System designed to facilitate entities moving about and interacting inside the game world
		class RTPhysics : public System {
			static const int PerPass;
			bool isEnabled = false;
			void ProcessMomentums(const EngineState& lastState, EngineState& newState);
			void ProcessPositions(const EngineState& lastState, EngineState& newState);
			void ProcessRotations(const EngineState& lastState, EngineState& newState);
			void ProcessCollisions(const EngineState& lastState, EngineState& newState);
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

		// System designed to provide all needed game logic while the game status is paused
		class PausedSystemsPack : public System {
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};

		// System designed to provide all needed game logic while the game is at the board view
		class BoardSystemsPack : public System {
            EntityID selection;
            EntityID mouseOver;
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};

		// System designed to provide all needed game logic while the game is at the combat view
		class CombatSystemsPack : public System {
		public:
			void Run(const EngineState& lastState, EngineState& newState);
		};

		// System designed to provide facilitate user input modifying gamestate
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

			//ActionEvent
			// Holds data related to a specific user input instance
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

        class IntroSystem : public System {
            Transform BaseTransform;
            Transform BCIT_Transform;
            Transform BCIT_square_transform;
            Transform BCIT_b_transform;
            Transform BCIT_c_transform;
            Transform BCIT_i_transform;
            Transform BCIT_t_transform;
            Model BCIT_square_model;
            Model BCIT_b_model;
            Model BCIT_c_model;
            Model BCIT_i_model;
            Model BCIT_t_model;
        public:
            IntroSystem();
            void Run(const EngineState& lastState, EngineState& newState);
        };
		class Networking
		{
		public:
			Networking();
			~Networking();
			void Run(Engine::EngineStateManager& stateManager);
		};
	}
}