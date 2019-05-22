#pragma once

#include "Components.h"
#include "EntityID.h"

namespace ECS {

	using namespace ECS::Components;


	class Entity {
	public:
		static EntityID NEXTID;

		ComponentMask* componentMask;

		Health* health;
		Damage* damage;
		Power* power;

        Transform* boardTransform;
        Model* boardModel;
		BoardPosition* boardPosition;
        BoardPiece* boardPiece;
		BoardMovement* boardMovement;

        Transform* combatTransform;
		Momentum* momentum;
		Momentum* rotationalMomentum;
        Model* combatModel;
		CollisionBody* combatCollisionBody;
        CombatSpeed* combatSpeed;

		TeamAffiliation* team;

		TerrainType* terrainType;

		AIStatus* ai;

		EntityID id;

	};
}