#pragma once

#include "Common.h"
#include "Graphics.h"
#include "Transform.h"
#include "Board.h"

namespace ECS {


	namespace Components {
		typedef uint64_t Mask_t;

		enum ComponentMask : Mask_t {
			None_m = 0b0,

			Health_m =              1ui64 << 1,
            Damage_m =              1ui64 << 2,
            Power_m =               1ui64 << 3,

            BoardTransform_m =      1ui64 << 5,
            BoardModel_m =          1ui64 << 6,
            BoardPosition_m =       1ui64 << 7,
            BoardPiece_m =          1ui64 << 8,
            BoardMovement_m =       1ui64 << 9,

            CombatTransform_m =     1ui64 << 10,
            Momentum_m =            1ui64 << 11,
            RotationalMomentum_m =  1ui64 << 12,
            CombatModel_m =         1ui64 << 13,
            CombatCollisionBody_m = 1ui64 << 14,
            CombatSpeed_m =         1ui64 << 15,

            TeamAffiliation_m =     1ui64 << 20,

            AiStatus_m =            1ui64 << 25,

            TerrainType_m =         1ui64 << 30,

            ControlPick_m =         1ui64 << 35
		};

        enum Entity_templates : Mask_t {
            BoardTileTemplate = BoardTransform_m | BoardModel_m | BoardPosition_m | TerrainType_m | ControlPick_m,
            BoardPieceTemplate = BoardTransform_m | BoardModel_m | BoardPosition_m | Health_m | Power_m | ControlPick_m | BoardPiece_m | TeamAffiliation_m,
            CombatPieceTemplate = CombatTransform_m | CombatModel_m | Momentum_m | RotationalMomentum_m | CombatCollisionBody_m | Health_m,
            CombatBulletTemplate = CombatTransform_m | CombatModel_m | Momentum_m | RotationalMomentum_m | CombatCollisionBody_m | Damage_m
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

		typedef int CombatSpeed;

		typedef int Health;
		typedef Health Damage;
		typedef Health Power;


		typedef float TimeStamp;

		enum TerrainType : Mask_t {
			Walkable = (1ui64 << 31),
			Flyable = (1ui64 << 30),
			Swimmable = (1ui64 << 29),

			FlatGround = 1ui64 | Walkable | Flyable,
			Water = (1ui64 << 1) | Flyable | Swimmable,
			Cave = (1ui64 << 2) | Walkable | Swimmable,
			Mountain = (1ui64 << 3) | Flyable,
			Storm = (1ui64 << 4)
		};

		enum NetworkStatus : Mask_t {

		};

		enum AIStatus : Mask_t {
            NoAI = 0
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
#define DefaultTransform {}
#define DefaultModel {}
	}
}