#pragma once

#include "Common.h"

namespace ECS {


	namespace Components {
		typedef int32_t Mask_t;

		enum ComponentMask : Mask_t {
			None_m = 0b0,

			BoardVisual_m = 0b1,
			BoardCollisionBody_m = 0b1 << 1,
			BoardPosition_m = 0b1 << 2,

			RealTimeVisual_m = 0b1 << 3,
			RealTimePosition_m = 0b1 << 4,
			RealTimeMomentum_m = 0b1 << 5,
			RealTimeRotation_m = 0b1 << 6,
			RotationalMomentum_m = 0b1 << 7,
			RealTimeCollisionBody_m = 0b1 << 8,

			Health_m = 0b1 << 9,
			Damage_m = 0b1 << 10,
			Power_m = 0b1 << 11,

			BoardSpeed_m = 0b1 << 12,
			RealtimeSpeed_m = 0b1 << 13,

			TeamAffiliation_m = 0b1 << 14,

			TerrainType_m = 0b1 << 15,


		};

		constexpr inline ComponentMask operator|(const ComponentMask& lhs, const ComponentMask& rhs){
			return (ComponentMask)((Mask_t)lhs | (Mask_t)rhs);
		};

		constexpr inline ComponentMask operator&(const ComponentMask& lhs, const ComponentMask& rhs) {
			return (ComponentMask)((Mask_t)lhs & (Mask_t)rhs);
		};


		typedef glm::vec3 Position;
		typedef glm::vec3 Rotation;
		typedef glm::vec3 Momentum;

		typedef glm::vec3 CollisionBody;

		typedef int BoardSpeed;
		typedef int RealtimeSpeed;

		typedef int Health;
		typedef Health Damage;
		typedef Health Power;

		enum Visual {
			Unassigned_v,

			Terrain_v,

			Pawn_v,
			Knight_v,
			Queen_v,

			Bullet_v
		};


		typedef float TimeStamp;

		enum TerrainType : Mask_t {
			Walkable = (0b1 << 31),
			Flyable = (0b1 << 30),
			Swimmable = (0b1 << 29),

			FlatGround = 0b1 | Walkable | Flyable,
			Water = (0b1 << 1) | Flyable | Swimmable,
			Cave = (0b1 << 2) | Walkable | Swimmable,
			Mountain = (0b1 << 3) | Flyable,
			Storm = (0b1 << 4)
		};

		enum NetworkStatus : Mask_t {

		};

		enum AIStatus : Mask_t {

		};

		enum EventID : Mask_t {

		};

		enum PlayerType : Mask_t {
			Human,
			AI
		};

		enum TeamAffiliation {
			Neutral,
			Player1,
			Player2
		};

#define DefaultPos {-9000,-9000,9000}
#define DefaultMom {0,0,0}
#define DefaultRot {0,0,0}
#define DefaultCol {1,1,1}
#define DefaultHealth 1
#define DefaultSpeed 1
	}
}