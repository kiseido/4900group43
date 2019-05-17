#pragma once

#include "Common.h"

namespace ECS {
	namespace Components {
		typedef int32_t Mask_t;

		enum ComponentMask : Mask_t {
			BoardVisual = 0b1,
			BoardCollisionBody = 0b1 << 1,
			BoardPosition = 0b1 << 2,

			RealTimeVisual = 0b1 << 3,
			RealTimePosition = 0b1 << 4,
			RealTimeMomentum = 0b1 << 5,
			RealTimeRotation = 0b1 << 6,
			RotationalMomentum = 0b1 << 7,
			RealTimeCollisionBody = 0b1 << 8
		};

		class Component {
		public:
			constexpr ComponentMask getMask();
		};

		typedef glm::vec3 Position;
		typedef glm::vec3 Rotation;
		typedef glm::vec3 Momentum;

		typedef glm::vec3 CollisionBody;

		typedef int Health;

		typedef char Visual;
		typedef float TimeStamp;
	}
}